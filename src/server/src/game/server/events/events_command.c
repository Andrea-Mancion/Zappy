/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side : run method
*/

#include "zappy_misc.h"
#include "game/server_class.h"
#include "zappy_game.h"
#include "game/command_class.h"
#include "game/event_class.h"

static const char *error_message = "Couldn't execute ai command";
static const char *ko_message = "ko";

// Finds the command in the table and executes it, returns false if not found
static int execute_ai_command(game_server_t *server, game_client_t *client,
    pending_command_t *command, char **args)
{
    for (int i = 0; ai_commands_table[i].command; i++) {
        if (strcmp(ai_commands_table[i].command, args[0]) != 0)
            continue;
        command->duration = ai_commands_table[i].duration;
        return ai_commands_table[i].function(server, client, args + 1,
            &command->output);
    }
    return ERR_COMMAND;
}

// Parses a client-given command and executes it
static int parse_ai_command(game_server_t *server, game_client_t *client,
    pending_command_t *command)
{
    char **args = malloc(sizeof(char *) * (strlen(command->input) + 1));
    int j = 0;
    int status = ERR_COMMAND;

    for (char *sub = strtok(command->input, " "); sub; sub = strtok(NULL, " "))
        args[j++] = sub;
    args[j] = NULL;
    if (!args[0] || (status = execute_ai_command(
        server, client, command, args)) != SUCCESS) {
        free(args);
        return status;
    }
    free(args);
    return SUCCESS;
}

// Starts the command's execution
void event_start_command(game_server_t *server,
    game_client_t *client)
{
    pending_command_t *cmd = client->commands.get(&client->commands, 0);
    event_params_t params = {tick(), cmd->duration * 1e6,
        PLAYER_COMMAND, client};

    if (cmd->output)
        return;
    if (!handle_error(parse_ai_command(server, client, cmd),
        error_message)) {
        cmd->output = strdup(ko_message);
        event_end_command(server, client);
    } else
        server->add_event(server, &params);
}

// Sends the command's output to the client and removes it from the list
void event_end_command(game_server_t *server, game_client_t *client)
{
    pending_command_t *cmd = client->commands.get(&client->commands, 0);

    if (!cmd) {
        printf("No command to end, event missing or invalid timeout\n");
        return;
    }
    dprintf(client->socket, "%s\n", cmd->output);
    client->commands.remove(&client->commands, 0);
    if (client->commands.size > 0)
        event_start_command(server, client);
}
