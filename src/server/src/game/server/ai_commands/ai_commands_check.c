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

static const int direction_increment_left[][2] = {
    [NORTH] = {-1, 0},
    [EAST] = {0, -1},
    [SOUTH] = {1, 0},
    [WEST] = {0, 1},
};

static void get_tile_content(game_tile_t *tile, char *buffer)
{
    int *addresses[] = {[FOOD] = &tile->food, [LINEMATE] = &tile->linemate,
        [DERAUMERE] = &tile->deraumere, [SIBUR] = &tile->sibur, [MENDIANE] =
        &tile->mendiane, [PHIRAS] = &tile->phiras, [THYSTAME] =
        &tile->thystame};
    bool is_there_even_something = false;

    for (int i = 0; i < RESOURCE_COUNT; i++) {
        for (int j = 0; j < *addresses[i]; j++) {
            strcat(buffer, resource_names[i]);
            strcat(buffer, " ");
            is_there_even_something = true;
        }
    }
    if (tile->players.size == 0 && is_there_even_something)
        buffer[strlen(buffer) - 1] = '\0';
    for (int j = 0; j < tile->players.size; j++) {
        strcat(buffer, "player");
        if (j < tile->players.size - 1)
            strcat(buffer, " ");
    }
}

static void get_line_content(game_map_t *map, game_client_t *client, char *
    buffer, int range)
{
    int x = client->x, y = client->y;
    int forward_increment[2], left_increment[2];

    forward_increment[0] = direction_increment_forward[client->direction][0];
    forward_increment[1] = direction_increment_forward[client->direction][1];
    left_increment[0] = direction_increment_left[client->direction][0];
    left_increment[1] = direction_increment_left[client->direction][1];
    for (int i = 0; i < 1 + range * 2; i++) {
        int pos[2] = {x + forward_increment[0] * range + left_increment[0] *
            (i - range), y + forward_increment[1] * range + left_increment[1] *
            (i - range)};
        pos[0] %= map->width;
        pos[1] %= map->height;
        pos[0] = pos[0] < 0 ? map->width + pos[0] : pos[0];
        pos[1] = pos[1] < 0 ? map->height + pos[1] : pos[1];
        if (i != 0)
            strcat(buffer, ", ");
        get_tile_content(&map->tiles[pos[1]][pos[0]], buffer);
    }
}

// Look command
int ai_command_look(game_server_t *server, game_client_t *client,
    ATTR_UNUSED char **args, char **output)
{
    (void)server;
    (void)client;
    char buffer[BUFFER_SIZE] = {0};

    buffer[0] = '[';
    for (int i = 0; i < client->level + 1; i++) {
        if (i != 0)
            strcat(buffer, ", ");
        get_line_content(&server->map, client, buffer, i);
    }
    strcat(buffer, "]");
    *output = strdup(buffer);
    return SUCCESS;
}

// Inventory command
int ai_command_inventory(ATTR_UNUSED game_server_t *server, game_client_t *
    client, ATTR_UNUSED char **args, char **output)
{
    char buffer[BUFFER_SIZE] = {0};

    sprintf(buffer, "[food %d, linemate %d, deraumere %d, sibur %d, mendiane "
        "%d, phiras %d, thystame %d]", client->inventory[FOOD],
        client->inventory[LINEMATE], client->inventory[DERAUMERE],
        client->inventory[SIBUR], client->inventory[MENDIANE],
        client->inventory[PHIRAS], client->inventory[THYSTAME]);
    *output = strdup(buffer);
    return SUCCESS;
}
