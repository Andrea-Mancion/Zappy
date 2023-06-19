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

// Forward command
int ai_command_forward(game_server_t *server, game_client_t *client,
    ATTR_UNUSED char **args, char **output)
{
    if (client->direction == NORTH)
        client->y = (client->y - 1) % server->map.height;
    else if (client->direction == EAST)
        client->x = (client->x + 1) % server->map.width;
    if (client->direction == SOUTH)
        client->y = (client->y + 1) % server->map.height;
    else if (client->direction == WEST)
        client->x = (client->x - 1) % server->map.width;
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
    client->direction = (client->direction - 1) % DIRECTION_COUNT;
    *output = strdup("ok");
    return SUCCESS;
}
