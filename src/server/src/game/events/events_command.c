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
#include "game/notification_class.h"
#include "game/event_class.h"

static const char *error_message = "Couldn't execute ai command";
static const char *ko_message = "ko";

// Finds the command in the table and executes it, returns false if not found
static int execute_ai_command(game_t *game, game_client_t *client,
    pending_command_t *command, char **args)
{
    for (int i = 0; ai_commands_table[i].command; i++) {
        if (strcmp(ai_commands_table[i].command, args[0]) != 0)
            continue;
        command->duration = ai_commands_table[i].duration;
        return ai_commands_table[i].function(game, client, args + 1,
            command);
    }
    printf("Command not found: \"%s\"\n", args[0]);
    return ERR_COMMAND;
}

// Parses a client-given command and executes it
static int parse_ai_command(game_t *game, game_client_t *client,
    pending_command_t *command)
{
    char *args[strlen(command->input) + 1];
    int j = 0;
    int status = ERR_COMMAND;

    for (char *sub = strtok(command->input, " "); sub; sub = strtok(NULL, " "))
        args[j++] = sub;
    args[j] = NULL;
    if (!args[0] || (status = execute_ai_command(game, client, command, args)
        ) != SUCCESS)
        return status;
    return SUCCESS;
}

// Starts the command's execution
void event_start_command(game_t *game, game_client_t *client)
{
    pending_command_t *cmd = client->commands.get(&client->commands, 0);
    event_params_t params = {tick(), 0, PLAYER_COMMAND, client};

    if (!cmd || cmd->output)
        return;
    if (!handle_error(parse_ai_command(game, client, cmd),
        error_message)) {
        cmd->output = strdup(ko_message);
        event_end_command(game, client);
    } else {
        params.duration = cmd->duration * 1e6;
        game->add_event(game, &params);
    }
}

// Broadcasts a message to every player
void broadcast_to_players(game_t *game, game_client_t *client, char *message)
{
    game_client_t *player;

    for (int i = 0; i < game->server.clients.size; i++) {
        player = game->server.clients.get(&game->server.clients, i);
        if (strcmp(player->team_name, "GRAPHIC") == 0 || player == client)
            continue;
        dprintf(player->socket, "message %d, %s\n",
            game->get_direction_from_broadcast(game, client, player), message);
    }
}

// Sends the command's output to the client and removes it from the list
void event_end_command(game_t *game, game_client_t *client)
{
    pending_command_t *cmd = client->commands.get(&client->commands, 0);
    graphic_notification_pair_t *pair;
    if (!cmd || tick() - cmd->received_at < ((cmd->duration * 1e6) / game->
        frequency))
        return;
    dprintf(client->socket, "%s\n", cmd->output);
    if (cmd->output && strcmp(cmd->output, ko_message) != 0) {
        for (int i = 0; i < cmd->graphic_notifications.size; i++) {
            pair = cmd->graphic_notifications.get(&cmd->graphic_notifications,
                i);
            game->notify_all_graphic(game, pair->command, &pair->params);
            free(pair->params.message);
            free(pair->params.team_name);
        }
        if (cmd->broadcast)
            broadcast_to_players(game, client, cmd->broadcast);
    }
    client->commands.remove(&client->commands, 0);
    if (client->commands.size > 0)
        event_start_command(game, client);
}
