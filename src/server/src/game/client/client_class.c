/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - client class
*/

#include <unistd.h>
#include "zappy_misc.h"
#include "zappy_game.h"
#include "game/client_class.h"
#include "game/map_class.h"

// Initial structure of client
const game_client_t default_client = {
    .socket = -1,
    .team_name = NULL,
    .buffer = NULL,
    .id = -1,
    .direction = EAST,
    .x = 0,
    .y = 0,
    .commands = {0},
    .level = 1,
    .inventory = {
        [FOOD] = 10,
        [LINEMATE] = 0,
        [DERAUMERE] = 0,
        [SIBUR] = 0,
        [MENDIANE] = 0,
        [PHIRAS] = 0,
        [THYSTAME] = 0,
    },
    .destroy = &client_destroy,
};

// Initial structure of pending command
const pending_command_t default_command = {
    .input = NULL,
    .received_at = -1,
    .duration = -1,
    .output = NULL,
    .destroy = &pending_command_destroy,
};

// Client constructor
int client_init(game_client_t *client, int socket)
{
    if (socket < 0)
        return ERR_SOCKET;
    *client = default_client;
    client->socket = socket;
    if (!(client->buffer = malloc(sizeof(char) * BUFFER_SIZE)))
        return ERR_ALLOC;
    memset(client->buffer, '\0', BUFFER_SIZE);
    list_init(&client->commands, (void (*)(void *))&pending_command_destroy,
        NULL);
    return SUCCESS;
}

// Initializes a client as a player
void client_init_as_ai(game_client_t *client, game_map_t *map)
{
    static int id = 0;
    int *player_id;

    client->direction = rand() % DIRECTION_COUNT;
    client->x = rand() % map->width;
    client->y = rand() % map->height;
    client->id = ++id;
    player_id = malloc(sizeof(int));
    *player_id = client->id;
    map->tiles[client->y][client->x].players.add(&map->tiles[client->y]
        [client->x].players, player_id);
}

// Client destructor
void client_destroy(game_client_t *client)
{
    if (client->socket >= 0)
        close(client->socket);
    if (client->team_name)
        free(client->team_name);
    if (client->buffer)
        free(client->buffer);
    client->commands.destroy(&client->commands);
}

// Client command constructor
int pending_command_init(pending_command_t *command, char *input)
{
    *command = default_command;
    command->input = strdup(input);
    if (!command->input)
        return ERR_ALLOC;
    list_init(&command->graphic_notifications, NULL, NULL);
    return SUCCESS;
}

// Client command destructor
void pending_command_destroy(pending_command_t *command)
{
    if (command->input)
        free(command->input);
    if (command->output)
        free(command->output);
    command->graphic_notifications.destroy(&command->graphic_notifications);
}
