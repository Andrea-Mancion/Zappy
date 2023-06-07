/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - movement commands
*/

#include "zappy_misc.h"
#include "game/server_class.h"
#include "zappy_game.h"

// Forward command
int command_forward(game_server_t *server, game_client_t *client,
    ATTR_UNUSED char **args)
{
    if (client->direction == NORTH)
        client->y = (client->y - 1) % server->map.height;
    else if (client->direction == EAST)
        client->x = (client->x + 1) % server->map.width;
    if (client->direction == SOUTH)
        client->y = (client->y + 1) % server->map.height;
    else if (client->direction == WEST)
        client->x = (client->x - 1) % server->map.width;
    dprintf(client->socket, "ok\n");
    return SUCCESS;
}

// Right command
int command_right(ATTR_UNUSED game_server_t *server, game_client_t *client,
    ATTR_UNUSED char **args)
{
    client->direction = (client->direction + 1) % DIRECTION_COUNT;
    dprintf(client->socket, "ok\n");
    return SUCCESS;
}

// Left command
int command_left(ATTR_UNUSED game_server_t *server, game_client_t *client,
    ATTR_UNUSED char **args)
{
    client->direction = (client->direction - 1) % DIRECTION_COUNT;
    dprintf(client->socket, "ok\n");
    return SUCCESS;
}
