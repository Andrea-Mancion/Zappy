/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - object commands
*/

#include "zappy_misc.h"
#include "game/server_class.h"
#include "game/client_class.h"
#include "zappy_game.h"

const char *resource_names[] = {
    [FOOD] = "food",
    [LINEMATE] = "linemate",
    [DERAUMERE] = "deraumere",
    [SIBUR] = "sibur",
    [MENDIANE] = "mendiane",
    [PHIRAS] = "phiras",
    [THYSTAME] = "thystame",
};

// Get resource address from tile
static int *get_resource_address(game_server_t *server, game_client_t *client,
    game_resource_t resource)
{
    game_tile_t *tile = &server->map.tiles[client->y][client->x];
    int *resources_addresses[] = {[FOOD] = &tile->food, [LINEMATE] =
        &tile->linemate, [DERAUMERE] = &tile->deraumere, [SIBUR] =
        &tile->sibur, [MENDIANE] = &tile->mendiane, [PHIRAS] = &tile->phiras,
        [THYSTAME] = &tile->thystame};

    return resources_addresses[resource];
}

// Take command
int ai_command_take(game_server_t *server, game_client_t *client,
    char **args, char **output)
{
    game_resource_t enum_resource = RESOURCE_COUNT;
    int *address;

    if (args[0] == NULL)
        return ERR_COMMAND;
    for (int i = 0; i < RESOURCE_COUNT; i++)
        if (strcmp(args[0], resource_names[i]) == 0)
            enum_resource = i;
    if (enum_resource == RESOURCE_COUNT)
        return ERR_COMMAND;
    if (!*(address = get_resource_address(server, client, enum_resource))) {
        *output = strdup("ko");
        return SUCCESS;
    }
    *address -= 1;
    client->inventory[enum_resource] += 1;
    *output = strdup("ok");
    return SUCCESS;
}

// Set command
int ai_command_set(game_server_t *server, game_client_t *client,
    char **args, char **output)
{
    game_resource_t enum_resource = RESOURCE_COUNT;
    int *address;

    if (args[0] == NULL)
        return ERR_COMMAND;
    for (int i = 0; i < RESOURCE_COUNT; i++)
        if (strcmp(args[0], resource_names[i]) == 0)
            enum_resource = i;
    if (enum_resource == RESOURCE_COUNT)
        return ERR_COMMAND;
    address = get_resource_address(server, client, enum_resource);
    if (client->inventory[enum_resource] == 0) {
        *output = strdup("ko");
        return SUCCESS;
    }
    *address += 1;
    client->inventory[enum_resource] -= 1;
    *output = strdup("ok");
    return SUCCESS;
}

// Connect_nbr command
int ai_command_connect_nbr(game_server_t *server, game_client_t *client,
    ATTR_UNUSED char **args, char **output)
{
    int count = 0;
    list_t *team = server->teams.get(&server->teams, client->team_name);
    char outp[10] = {0};

    count = server->max_team_capacity - team->size;
    sprintf(outp, "%d", count);
    *output = strdup(outp);
    return SUCCESS;
}
