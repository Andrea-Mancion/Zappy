/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - commands
*/

#include "zappy_misc.h"
#include "zappy_game.h"
#include "game/notification_class.h"
#include "game/command_class.h"

// msz graphic command
int graphic_command_msz(game_t *game, game_client_t *client,
    char **args)
{
    graphic_notification_params_t params = default_graphic_notification_params;

    if (args[0]) {
        graphic_notification_sbp(game, client, &params);
        return ERR_COMMAND;
    }
    graphic_notification_msz(game, client, &params);
    return SUCCESS;
}

// bct graphic command
int graphic_command_bct(game_t *game, game_client_t *client,
    char **args)
{
    graphic_notification_params_t params = default_graphic_notification_params;

    if (!args[0] || !args[1] || args[2]) {
        graphic_notification_sbp(game, client, &params);
        return ERR_COMMAND;
    }
    params.x = atoi(args[0]);
    params.y = atoi(args[1]);
    if (params.x < 0 || params.x >= game->map.width || params.y < 0 ||
        params.y >= game->map.height) {
        graphic_notification_sbp(game, client, &params);
        return ERR_COMMAND;
    }
    graphic_notification_bct(game, client, &params);
    return SUCCESS;
}

// mct graphic command
int graphic_command_mct(game_t *game, game_client_t *client,
    char **args)
{
    graphic_notification_params_t params = default_graphic_notification_params;

    if (args[0]) {
        graphic_notification_sbp(game, client, &params);
        return ERR_COMMAND;
    }
    graphic_notification_mct(game, client, &params);
    return SUCCESS;
}

// sst graphic command
int graphic_command_sst(game_t *game, game_client_t *client,
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
    game->frequency = frequency;
    graphic_notification_sgt(game, client, &params);
    return SUCCESS;
}
