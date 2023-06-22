/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - commands
*/

#include "zappy_misc.h"
#include "zappy_game.h"
#include "game/command_class.h"

// msz graphic command
int graphic_command_msz(game_server_t *server, game_client_t *client,
    char **args)
{
    graphic_notification_params_t params = default_graphic_notification_params;

    if (args[0]) {
        graphic_notification_sbp(server, client, &params);
        return ERR_COMMAND;
    }
    graphic_notification_msz(server, client, &params);
    return SUCCESS;
}

// bct graphic command
int graphic_command_bct(game_server_t *server, game_client_t *client,
    char **args)
{
    graphic_notification_params_t params = default_graphic_notification_params;

    if (!args[0] || !args[1] || args[2]) {
        graphic_notification_sbp(server, client, &params);
        return ERR_COMMAND;
    }
    params.x = atoi(args[0]);
    params.y = atoi(args[1]);
    if (params.x < 0 || params.x >= server->map.width || params.y < 0 ||
        params.y >= server->map.height) {
        graphic_notification_sbp(server, client, &params);
        return ERR_COMMAND;
    }
    graphic_notification_bct(server, client, &params);
    return SUCCESS;
}

// mct graphic command
int graphic_command_mct(game_server_t *server, game_client_t *client,
    char **args)
{
    graphic_notification_params_t params = default_graphic_notification_params;

    if (args[0]) {
        graphic_notification_sbp(server, client, &params);
        return ERR_COMMAND;
    }
    graphic_notification_mct(server, client, &params);
    return SUCCESS;
}

// sst graphic command
int graphic_command_sst(game_server_t *server, game_client_t *client,
    char **args)
{
    graphic_notification_params_t params = default_graphic_notification_params;
    int frequency;

    if (!args[0] || args[1]) {
        dprintf(client->socket, "sbp\n");
        return ERR_COMMAND;
    }
    frequency = atoi(args[0]);
    if (frequency < 2 || frequency > 10000) {
        dprintf(client->socket, "sbp\n");
        return ERR_COMMAND;
    }
    server->frequency = frequency;
    graphic_notification_sgt(server, client, &params);
    return SUCCESS;
}
