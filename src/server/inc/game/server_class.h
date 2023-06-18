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
    #include "misc/map_class.h"
    #include "game/map_class.h"
    #include "game/client_class.h"

// Definitions
typedef struct timeval timeval_t;
typedef struct sockaddr_in sockaddr_in_t;
typedef struct game_server_s game_server_t;

// Server class
struct game_server_s {
    int socket;
    sockaddr_in_t address;
    list_t clients;
    list_t events;
    map_t teams;
    game_map_t map;
    timeval_t timeout;
    int max_team_capacity;
    int frequency;
    // Events
    bool (*add_event)(game_server_t *server, void *params);
    bool (*remove_events)(game_server_t *server, game_event_type_t type,
        game_client_t *client);
    // Client
    int (*accept_client)(game_server_t *server);
    int (*init_client)(game_server_t *server, game_client_t *client, char *
        team);
    bool (*read_client)(game_server_t *server, game_client_t *client);
    void (*disconnect_client)(game_server_t *server, game_client_t *client);
    // Select
    int (*select)(game_server_t *server);
    // Run
    int (*run)(game_server_t *server);
    // Util
    game_client_t *(*get_player)(game_server_t *server, int id);
    void (*set_timeout)(game_server_t *server);
    long long int (*get_timeout)(game_server_t *server);
    // Dtor
    void (*destroy)(game_server_t *server);
};

// Server ctor and dtor
int server_init(game_server_t *server, program_params_t *params);
void server_destroy(game_server_t *server);
// Run and select methods
int server_run(game_server_t *server);
int server_select(game_server_t *server);
// Util methods
game_client_t *server_get_player(game_server_t *server, int id);
void server_set_timeout(game_server_t *server);
long long int server_get_timeout(game_server_t *server);
// Event-related methods
bool server_add_event(game_server_t *server, void *params);
bool server_remove_events(game_server_t *server, game_event_type_t type,
    game_client_t *client);
// Client-related methods
int server_accept_client(game_server_t *server);
int server_init_client(game_server_t *server, game_client_t *client, char *
    team);
bool server_read_client(game_server_t *server, game_client_t *client);
void server_disconnect_client(game_server_t *server, game_client_t *client);

#endif
