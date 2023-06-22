/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - notifications
*/

#include "zappy_misc.h"
#include "zappy_game.h"
#include "game/command_class.h"

// pnw graphic notification
void graphic_notification_pnw(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params)
{
    game_client_t *player = server->get_player(server, params->id);

    dprintf(client->socket, "pnw %d %d %d %d %d %s\n", player->id,
        player->x, player->y, player->direction,
        player->level, player->team_name);
}
