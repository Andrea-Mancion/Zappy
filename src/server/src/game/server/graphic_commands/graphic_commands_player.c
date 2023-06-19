/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - commands
*/

#include "zappy_misc.h"
#include "zappy_game.h"
#include "game/command_class.h"

// tna graphic command
int graphic_command_tna(game_server_t *server, game_client_t *client,
    char **args)
{
    if (args[0]) {
        dprintf(client->socket, "sbp\n");
        return ERR_COMMAND;
    }
    for (map_node_t *node = server->teams.head; node; node = node->next)
        dprintf(client->socket, "tna %s\n", (char *)node->key);
    return SUCCESS;
}

// ppo graphic command
int graphic_command_ppo(game_server_t *server, game_client_t *client,
    char **args)
{
    game_client_t *target;

    if (!args[0] || args[1]) {
        dprintf(client->socket, "sbp\n");
        return ERR_COMMAND;
    }
    target = server->get_player(server, atoi(args[0]));
    if (!target) {
        dprintf(client->socket, "sbp\n");
        return ERR_COMMAND;
    }
    dprintf(client->socket, "ppo %d %d %d %d\n", target->id, target->x,
        target->y, target->direction + 1);
    return SUCCESS;
}

// plv graphic command
int graphic_command_plv(game_server_t *server, game_client_t *client,
    char **args)
{
    game_client_t *target;

    if (!args[0] || args[1]) {
        dprintf(client->socket, "sbp\n");
        return ERR_COMMAND;
    }
    target = server->get_player(server, atoi(args[0]));
    if (!target) {
        dprintf(client->socket, "sbp\n");
        return ERR_COMMAND;
    }
    dprintf(client->socket, "plv %d %d\n", target->id, target->level);
    return SUCCESS;
}

// pin graphic command
int graphic_command_pin(game_server_t *server, game_client_t *client,
    char **args)
{
    game_client_t *target;

    if (!args[0] || args[1]) {
        dprintf(client->socket, "sbp\n");
        return ERR_COMMAND;
    }
    target = server->get_player(server, atoi(args[0]));
    if (!target) {
        dprintf(client->socket, "sbp\n");
        return ERR_COMMAND;
    }
    dprintf(client->socket, "pin %d %d %d %d %d %d %d %d %d %d\n", target->id,
        target->x, target->y, target->inventory[FOOD], target->inventory
        [LINEMATE], target->inventory[DERAUMERE], target->inventory[SIBUR],
        target->inventory[MENDIANE], target->inventory[PHIRAS],
        target->inventory[THYSTAME]);
    return SUCCESS;
}

// sgt graphic command
int graphic_command_sgt(game_server_t *server, game_client_t *client,
    char **args)
{
    if (args[0]) {
        dprintf(client->socket, "sbp\n");
        return ERR_COMMAND;
    }
    dprintf(client->socket, "sgt %d\n", server->frequency);
    return SUCCESS;
}
