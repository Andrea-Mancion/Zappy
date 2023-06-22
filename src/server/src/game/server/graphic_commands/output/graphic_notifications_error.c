/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - notifications
*/

#include "zappy_misc.h"
#include "zappy_game.h"
#include "game/command_class.h"

// tna graphic notification
void graphic_notification_suc(ATTR_UNUSED game_server_t *server,
    game_client_t *client, ATTR_UNUSED graphic_notification_params_t *params)
{
    dprintf(client->socket, "suc\n");
}

// ppo graphic notification
void graphic_notification_sbp(ATTR_UNUSED game_server_t *server,
    game_client_t *client, ATTR_UNUSED graphic_notification_params_t *params)
{
    dprintf(client->socket, "sbp\n");
}
