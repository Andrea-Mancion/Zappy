/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - movement commands
*/

#include "zappy_misc.h"
#include "game/server_class.h"
#include "game/client_class.h"
#include "zappy_game.h"

static const int direction_increment_forward[][2] = {
    [NORTH] = {0, -1},
    [EAST] = {1, 0},
    [SOUTH] = {0, 1},
    [WEST] = {-1, 0},
};

// Forward command
int ai_command_forward(game_server_t *server, game_client_t *client,
    ATTR_UNUSED char **args, char **output)
{
    int index = server->map.tiles[client->y][client->x].players.index(
        &server->map.tiles[client->y][client->x].players, &client->id);
    int *player = malloc(sizeof(int));

    *player = client->id;
    server->map.tiles[client->y][client->x].players.remove(
        &server->map.tiles[client->y][client->x].players, index);
    client->x = (client->x + direction_increment_forward[client->direction][0]
        + server->map.width) % server->map.width;
    client->y = (client->y + direction_increment_forward[client->direction][1]
        + server->map.height) % server->map.height;
    server->map.tiles[client->y][client->x].players.add(
        &server->map.tiles[client->y][client->x].players, player);
    *output = strdup("ok");
    return SUCCESS;
}

// Right command
int ai_command_right(ATTR_UNUSED game_server_t *server, game_client_t *client,
    ATTR_UNUSED char **args, char **output)
{
    client->direction = (client->direction + 1) % DIRECTION_COUNT;
    *output = strdup("ok");
    return SUCCESS;
}

// Left command
int ai_command_left(ATTR_UNUSED game_server_t *server, game_client_t *client,
    ATTR_UNUSED char **args, char **output)
{
    client->direction = (client->direction - 1 + DIRECTION_COUNT) %
        DIRECTION_COUNT;
    *output = strdup("ok");
    return SUCCESS;
}
