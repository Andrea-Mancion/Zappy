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

// tna graphic command
int graphic_command_tna(game_t *game, game_client_t *client,
    char **args)
{
    graphic_notification_params_t params = default_graphic_notification_params;
    if (args[0]) {
        graphic_notification_sbp(game, client, &params);
        return ERR_COMMAND;
    }
    graphic_notification_tna(game, client, &params);
    return SUCCESS;
}

// ppo graphic command
int graphic_command_ppo(game_t *game, game_client_t *client,
    char **args)
{
    graphic_notification_params_t params = default_graphic_notification_params;
    game_client_t *target;

    if (!args[0] || args[1]) {
        graphic_notification_sbp(game, client, &params);
        return ERR_COMMAND;
    }
    params.id = atoi(args[0]);
    target = game->get_player(game, params.id);
    if (!target) {
        graphic_notification_sbp(game, client, &params);
        return ERR_COMMAND;
    }
    graphic_notification_ppo(game, client, &params);
    return SUCCESS;
}

// plv graphic command
int graphic_command_plv(game_t *game, game_client_t *client,
    char **args)
{
    graphic_notification_params_t params = default_graphic_notification_params;
    game_client_t *target;

    if (!args[0] || args[1]) {
        graphic_notification_sbp(game, client, &params);
        return ERR_COMMAND;
    }
    params.id = atoi(args[0]);
    target = game->get_player(game, params.id);
    if (!target) {
        graphic_notification_sbp(game, client, &params);
        return ERR_COMMAND;
    }
    graphic_notification_plv(game, client, &params);
    return SUCCESS;
}

// pin graphic command
int graphic_command_pin(game_t *game, game_client_t *client,
    char **args)
{
    graphic_notification_params_t params = default_graphic_notification_params;
    game_client_t *target;

    if (!args[0] || args[1]) {
        graphic_notification_sbp(game, client, &params);
        return ERR_COMMAND;
    }
    params.id = atoi(args[0]);
    target = game->get_player(game, params.id);
    if (!target) {
        graphic_notification_sbp(game, client, &params);
        return ERR_COMMAND;
    }
    graphic_notification_pin(game, client, &params);
    return SUCCESS;
}

// sgt graphic command
int graphic_command_sgt(game_t *game, game_client_t *client,
    char **args)
{
    graphic_notification_params_t params = default_graphic_notification_params;

    if (args[0]) {
        graphic_notification_sbp(game, client, &params);
        return ERR_COMMAND;
    }
    graphic_notification_sgt(game, client, &params);
    return SUCCESS;
}
