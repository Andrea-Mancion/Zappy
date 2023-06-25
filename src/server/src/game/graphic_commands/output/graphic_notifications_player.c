/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - notifications
*/

#include "zappy_misc.h"
#include "zappy_game.h"
#include "game/notification_class.h"
#include "game/command_class.h"

// tna graphic notification
void graphic_notification_tna(game_t *game, game_client_t *client,
    ATTR_UNUSED graphic_notification_params_t *params)
{
    for (map_node_t *node = game->teams.head; node; node = node->next)
        dprintf(client->socket, "tna %s\n", (char *)node->key);
}

// ppo graphic notification
void graphic_notification_ppo(ATTR_UNUSED game_t *game,
    game_client_t *client, ATTR_UNUSED graphic_notification_params_t *params)
{
    dprintf(client->socket, "ppo %d %d %d %d\n", params->id, params->x,
        params->y, params->direction + 1);
}

// plv graphic notification
void graphic_notification_plv(ATTR_UNUSED game_t *game,
    game_client_t *client, graphic_notification_params_t *params)
{
    dprintf(client->socket, "plv %d %d\n", params->id, params->level);
}

// pin graphic notification
void graphic_notification_pin(game_t *game, game_client_t *client,
    graphic_notification_params_t *params)
{
    game_client_t *target = game->get_player(game, params->id);

    dprintf(client->socket, "pin %d %d %d %d %d %d %d %d %d %d\n", target->id,
        target->x, target->y, target->inventory[FOOD], target->inventory
        [LINEMATE], target->inventory[DERAUMERE], target->inventory[SIBUR],
        target->inventory[MENDIANE], target->inventory[PHIRAS],
        target->inventory[THYSTAME]);
}

// pdi graphic notification
void graphic_notification_pdi(ATTR_UNUSED game_t *game,
    game_client_t *client, graphic_notification_params_t *params)
{
    dprintf(client->socket, "pdi %d\n", params->id);
}
