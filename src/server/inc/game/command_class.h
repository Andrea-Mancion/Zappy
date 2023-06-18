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

// Pair structure of the command table
typedef struct game_command_s {
    const char *command;
    int (*function)(game_server_t *server, game_client_t *client, char **args,
        char **output);
    int duration;
} game_command_t;

// Const variables
extern const game_command_t graphic_commands_table[];
extern const game_command_t ai_commands_table[];

// AI command functions
int ai_command_forward(game_server_t *server, game_client_t *client,
    char **args, char **output);
int ai_command_right(game_server_t *server, game_client_t *client, char **args,
    char **output);
int ai_command_left(game_server_t *server, game_client_t *client, char **args,
    char **output);
int ai_command_look(game_server_t *server, game_client_t *client, char **args,
    char **output);
int ai_command_inventory(game_server_t *server, game_client_t *client,
    char **args, char **output);
int ai_command_broadcast(game_server_t *server, game_client_t *client,
    char **args, char **output);
int ai_command_connect_nbr(game_server_t *server, game_client_t *client,
    char **args, char **output);
int ai_command_fork(game_server_t *server, game_client_t *client, char **args,
    char **output);
int ai_command_eject(game_server_t *server, game_client_t *client, char **args,
    char **output);
int ai_command_take(game_server_t *server, game_client_t *client, char **args,
    char **output);
int ai_command_set(game_server_t *server, game_client_t *client, char **args,
    char **output);
int ai_command_incantation(game_server_t *server, game_client_t *client,
    char **args, char **output);

#endif
