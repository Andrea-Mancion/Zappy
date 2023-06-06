/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - server class
*/

#ifndef ZAPPY_GAME_SERVER_H_

    #define ZAPPY_GAME_SERVER_H_

    #include <arpa/inet.h>
    #include <sys/select.h>

    #include "zappy_program.h"
    #include "misc/list_class.h"
    #include "misc/timer_class.h"
    #include "game/map_class.h"
    #include "game/client_class.h"

// Forward declarations
typedef struct game_server_s game_server_t;

// Pair structure of the command table
typedef struct command_pair_s {
    char *command;
    int (*function)(game_server_t *server, game_client_t *client, char **args);
} command_pair_t;

// Server class
typedef struct game_server_s {
    int socket;
    struct sockaddr_in address;
    struct timeval timeout;
    list_t client_list;
    game_map_t map;
    timer_millis_t timer;
    const command_pair_t *command_table;
    bool (*read_from_client)(struct game_server_s *server, game_client_t *
        client);
    int (*run)(struct game_server_s *server);
    void (*destroy)(struct game_server_s *server);
} game_server_t;

// Command table defined in a separate file
extern const command_pair_t command_table[];

// Server ctor, dtor and methods
int server_init(game_server_t *server, program_params_t *params);
int server_run(game_server_t *server);
bool server_read_from_client(game_server_t *server, game_client_t *client);
void server_destroy(game_server_t *server);

#endif
