/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - server class
*/

#include <unistd.h>
#include "zappy_misc.h"
#include "game/command_class.h"
#include "game/event_class.h"

static const char *welcome_message = "WELCOME";
static const char *error_command = "Couldn't handle command";
static const char *err_cm = "Couldn't execute graphic command";

// Directly deals with a graphic command
static int execute_graphic_command(game_server_t *server,
    game_client_t *client, char *command)
{
    char *args[strlen(command) + 1];
    int j = 0;

    for (char *sub = strtok(command, " "); sub; sub = strtok(NULL, " "))
        args[j++] = sub;
    args[j] = NULL;
    for (int i = 0; graphic_commands_table[i].command; i++)
        if (strcmp(graphic_commands_table[i].command, args[0]) == 0)
            return graphic_commands_table[i].function(server, client,
                args + 1);
    dprintf(client->socket, "suc\n");
    return ERR_COMMAND;
}

// Adds the given command from the client's buffer to the client's command list
static int handle_command(game_server_t *server, game_client_t *client,
    char *command)
{
    pending_command_t *cmd;
    int status;

    if (!client->team_name)
        return server->init_client(server, client, command);
    if (strcmp(client->team_name, "GRAPHIC") == 0) {
        handle_error(execute_graphic_command(server, client, command), err_cm);
        return SUCCESS;
    }
    cmd = malloc(sizeof(pending_command_t));
    if (!cmd)
        return ERR_ALLOC;
    if ((status = pending_command_init(cmd, command)) != SUCCESS) {
        pending_command_destroy(cmd);
        free(cmd);
        return status;
    }
    if (!client->commands.add(&client->commands, cmd))
        return ERR_ALLOC;
    return SUCCESS;
}

// Reads the buffer of the client, returns false if the client disconnected
bool server_read_client(game_server_t *server, game_client_t *client)
{
    char buffer[BUFFER_SIZE];
    int readlen = read(client->socket, buffer, BUFFER_SIZE);
    int buflen = strlen(client->buffer);

    if (readlen <= 0)
        return false;
    buffer[readlen] = '\0';
    strncat(client->buffer, buffer, BUFFER_SIZE - buflen - 1);
    if (buffer[readlen - 1] != '\n')
        return true;
    for (char *cmd = strtok(client->buffer, "\r\n"); cmd && client->
        commands.size <= MAX_PENDING_COMMANDS; cmd = strtok(NULL, "\r\n"))
        handle_error(handle_command(server, client, cmd), error_command);
    client->buffer[0] = '\0';
    if (client->commands.size >= 1)
        event_start_command(server, client);
    return true;
}

// Creates a new client and adds it to the client list
int server_accept_client(game_server_t *server)
{
    game_client_t *client = malloc(sizeof(game_client_t));
    int socket;
    int status;

    if ((socket = accept(server->socket, NULL, NULL)) < 0) {
        free(client);
        return ERR_SOCKET;
    }
    if ((status = client_init(client, socket)) != SUCCESS) {
        client->destroy(client);
        free(client);
        return status;
    }
    server->clients.add(&server->clients, client);
    dprintf(socket, "%s\n", welcome_message);
    return SUCCESS;
}

void server_disconnect_client(game_server_t *server,
    game_client_t *client)
{
    game_client_t *target;
    list_t *team = server->teams.get(&server->teams, client->team_name);
    int index;
    if (team)
        if ((index = team->index(team, &client->id)) < team->size)
            team->remove(team, index);
    team = &server->map.tiles[client->y][client->x].players;
    if ((index = team->index(team, &client->id)) < team->size)
        team->remove(team, index);
    server->remove_events(server, PLAYER_COMMAND, client);
    server->remove_events(server, PLAYER_REMOVE_HEALTH, client);
    for (int i = 0; i < server->clients.size; i++) {
        target = server->clients.get(&server->clients, i);
        if (target->team_name && strcmp(target->team_name, "GRAPHIC") == 0)
            dprintf(((game_client_t *)server->clients.get(&server->clients,
                i))->socket, "pdi %d\n", client->id);
    }
    if ((index = server->clients.index(&server->clients, client))
        < server->clients.size)
        server->clients.remove(&server->clients, index);
}
