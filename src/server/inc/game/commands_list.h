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

// Pair structure of the command table
typedef struct command_pair_s {
    const char *command;
    int (*function)(game_server_t *server, game_client_t *client, char **);
} command_pair_t;

// Const variables
extern const command_pair_t command_table[];

// Command functions
int command_forward(game_server_t *server, game_client_t *client, char **args);
int command_right(game_server_t *server, game_client_t *client, char **args);
int command_left(game_server_t *server, game_client_t *client, char **args);
int command_look(game_server_t *server, game_client_t *client, char **args);
int command_inventory(game_server_t *server, game_client_t *client, char **ar);
int command_broadcast(game_server_t *server, game_client_t *client, char **ar);
int command_connect_nbr(game_server_t *server, game_client_t *client, char **);
int command_fork(game_server_t *server, game_client_t *client, char **args);
int command_eject(game_server_t *server, game_client_t *client, char **args);
int command_take(game_server_t *server, game_client_t *client, char **args);
int command_set(game_server_t *server, game_client_t *client, char **args);
int command_incantation(game_server_t *server, game_client_t *client, char **);

#endif
