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

// pnw graphic notification
void graphic_notification_pnw(game_t *game, game_client_t *client,
    graphic_notification_params_t *params)
{
    game_client_t *player = game->get_player(game, params->id);

    dprintf(client->socket, "pnw %d %d %d %d %d %s\n", player->id,
        player->x, player->y, player->direction,
        player->level, player->team_name);
}

// pgt graphic notification
void graphic_notification_pgt(ATTR_UNUSED game_t *game, game_client_t *client,
    graphic_notification_params_t *params)
{
    dprintf(client->socket, "pgt %d %d\n", params->id, params->resource);
}

// pdr graphic notification
void graphic_notification_pdr(ATTR_UNUSED game_t *game, game_client_t *client,
    graphic_notification_params_t *params)
{
    dprintf(client->socket, "pdr %d %d\n", params->id, params->resource);
}
