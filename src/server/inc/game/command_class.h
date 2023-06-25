/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - game namespace
*/

#ifndef ZAPPY_GAME_COMMANDS_H_

    #define ZAPPY_GAME_COMMANDS_H_

    #include "zappy_game.h"
    #include "game/server_class.h"
    #include "game/client_class.h"

// Pair structure of the graphic command table
typedef struct game_ai_command_s {
    const char *command;
    int (*function)(game_t *game, game_client_t *client, char **args,
        pending_command_t *command);
    int duration;
} game_ai_command_t;

// Pair structure of the ai command table
typedef struct game_graphic_command_s {
    const char *command;
    int (*function)(game_t *game, game_client_t *client, char **args);
} game_graphic_command_t;

// Const variables
extern const game_graphic_command_t graphic_commands_table[];
extern const game_ai_command_t ai_commands_table[];

// AI command functions
int ai_command_forward(game_t *game, game_client_t *client,
    char **args, pending_command_t *command);
int ai_command_right(game_t *game, game_client_t *client, char **args,
    pending_command_t *command);
int ai_command_left(game_t *game, game_client_t *client, char **args,
    pending_command_t *command);
int ai_command_look(game_t *game, game_client_t *client, char **args,
    pending_command_t *command);
int ai_command_inventory(game_t *game, game_client_t *client,
    char **args, pending_command_t *command);
int ai_command_broadcast(game_t *game, game_client_t *client,
    char **args, pending_command_t *command);
int ai_command_connect_nbr(game_t *game, game_client_t *client,
    char **args, pending_command_t *command);
int ai_command_fork(game_t *game, game_client_t *client, char **args,
    pending_command_t *command);
int ai_command_eject(game_t *game, game_client_t *client, char **args,
    pending_command_t *command);
int ai_command_take(game_t *game, game_client_t *client, char **args,
    pending_command_t *command);
int ai_command_set(game_t *game, game_client_t *client, char **args,
    pending_command_t *command);
int ai_command_incantation(game_t *game, game_client_t *client,
    char **args, pending_command_t *command);

// Graphic command functions
int graphic_command_msz(game_t *game, game_client_t *client,
    char **args);
int graphic_command_bct(game_t *game, game_client_t *client,
    char **args);
int graphic_command_mct(game_t *game, game_client_t *client,
    char **args);
int graphic_command_tna(game_t *game, game_client_t *client,
    char **args);
int graphic_command_ppo(game_t *game, game_client_t *client,
    char **args);
int graphic_command_plv(game_t *game, game_client_t *client,
    char **args);
int graphic_command_pin(game_t *game, game_client_t *client,
    char **args);
int graphic_command_sgt(game_t *game, game_client_t *client,
    char **args);
int graphic_command_sst(game_t *game, game_client_t *client,
    char **args);

#endif
