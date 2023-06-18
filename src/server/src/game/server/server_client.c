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

// Give a team name to the client
static int give_team_name(game_server_t *server, game_client_t *client,
    char *command)
{
    list_t *team = server->teams.get(&server->teams, command);
    game_client_t **id;
    event_params_t params = {0, FOOD_TIME * 1e6, PLAYER_REMOVE_HEALTH, client};
    if (strcmp(command, "GRAPHIC") == 0) {
        client->team_name = strdup(command);
        return SUCCESS;
    } else if (!team) {
        dprintf(client->socket, "ko\n");
        return ERR_TEAM;
    }
    client_init_as_ai(client, &server->map);
    id = malloc(sizeof(game_client_t *));
    *id = client;
    team->add(team, id);
    client->team_name = strdup(command);
    params.start_time = tick();
    server->add_event(server, &params);
    dprintf(client->socket, "%d\n", server->max_team_capacity - team->size);
    dprintf(client->socket, "%d %d\n", server->map.width, server->map.height);
    return SUCCESS;
}

// Adds the given command from the client's buffer to the client's command list
static int add_command(game_server_t *server, game_client_t *client,
    char *command)
{
    pending_command_t *cmd;
    int status;

    if (!client->team_name)
        return give_team_name(server, client, command);
    cmd = malloc(sizeof(pending_command_t));
    if ((status = pending_command_init(cmd, command)) != SUCCESS) {
        pending_command_destroy(cmd);
        free(cmd);
        return status;
    }
    client->commands.add(&client->commands, cmd);
    return SUCCESS;
}

// Reads the buffer of the client, returns false if the client disconnected
bool server_read_client(game_server_t *server, game_client_t *client)
{
    char buffer[BUF_SIZE];
    int readlen = read(client->socket, buffer, BUF_SIZE);
    int buflen = strlen(client->buffer);

    if (readlen <= 0)
        return false;
    buffer[readlen] = '\0';
    strncat(client->buffer, buffer, BUF_SIZE - buflen - 1);
    if (buffer[readlen - 1] == '\n') {
        for (char *cmd = strtok(client->buffer, "\r\n"); cmd &&
            client->commands.size <= MAX_PENDING_COMMANDS;
            cmd = strtok(NULL, "\r\n"))
            add_command(server, client, cmd);
        client->buffer[0] = '\0';
        if (client->commands.size >= 1)
            event_start_command(server, client);
    }
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
    list_t *team = server->teams.get(&server->teams, client->team_name);
    int index;

    if (team) {
        index = team->index(team, &client);
        if (index < team->size)
            team->remove(team, index);
    }
    team = &server->map.tiles[client->y][client->x].players;
    index = team->index(team, &client);
    if (index < team->size)
        team->remove(team, index);
    server->remove_events(server, PLAYER_COMMAND, client);
    server->remove_events(server, PLAYER_REMOVE_HEALTH, client);
    index = server->clients.index(&server->clients, client);
    if (index < server->clients.size)
        server->clients.remove(&server->clients, index);
}
