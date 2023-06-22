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
    graphic_notification_params_t params = default_graphic_notification_params;
    if (args[0]) {
        graphic_notification_sbp(server, client, &params);
        return ERR_COMMAND;
    }
    graphic_notification_tna(server, client, &params);
    return SUCCESS;
}

// ppo graphic command
int graphic_command_ppo(game_server_t *server, game_client_t *client,
    char **args)
{
    graphic_notification_params_t params = default_graphic_notification_params;
    game_client_t *target;

    if (!args[0] || args[1]) {
        graphic_notification_sbp(server, client, &params);
        return ERR_COMMAND;
    }
    params.id = atoi(args[0]);
    target = server->get_player(server, params.id);
    if (!target) {
        graphic_notification_sbp(server, client, &params);
        return ERR_COMMAND;
    }
    graphic_notification_ppo(server, client, &params);
    return SUCCESS;
}

// plv graphic command
int graphic_command_plv(game_server_t *server, game_client_t *client,
    char **args)
{
    graphic_notification_params_t params = default_graphic_notification_params;
    game_client_t *target;

    if (!args[0] || args[1]) {
        graphic_notification_sbp(server, client, &params);
        return ERR_COMMAND;
    }
    params.id = atoi(args[0]);
    target = server->get_player(server, params.id);
    if (!target) {
        graphic_notification_sbp(server, client, &params);
        return ERR_COMMAND;
    }
    graphic_notification_plv(server, client, &params);
    return SUCCESS;
}

// pin graphic command
int graphic_command_pin(game_server_t *server, game_client_t *client,
    char **args)
{
    graphic_notification_params_t params = default_graphic_notification_params;
    game_client_t *target;

    if (!args[0] || args[1]) {
        graphic_notification_sbp(server, client, &params);
        return ERR_COMMAND;
    }
    params.id = atoi(args[0]);
    target = server->get_player(server, params.id);
    if (!target) {
        graphic_notification_sbp(server, client, &params);
        return ERR_COMMAND;
    }
    graphic_notification_pin(server, client, &params);
    return SUCCESS;
}

// sgt graphic command
int graphic_command_sgt(game_server_t *server, game_client_t *client,
    char **args)
{
    graphic_notification_params_t params = default_graphic_notification_params;

    if (args[0]) {
        graphic_notification_sbp(server, client, &params);
        return ERR_COMMAND;
    }
    graphic_notification_sgt(server, client, &params);
    return SUCCESS;
}
