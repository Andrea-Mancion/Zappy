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

    #include "misc/list_class.h"
    #include "misc/map_class.h"
    #include "game/map_class.h"
    #include "game/client_class.h"
    #include "zappy_program.h"
    #include "zappy_game.h"

// Definitions & forward declarations
typedef struct timeval timeval_t;
typedef struct sockaddr_in sockaddr_in_t;
typedef struct game_server_s game_server_t;
typedef struct graphic_notification_params_s graphic_notification_params_t;
typedef struct game_s game_t;

// Server class
struct game_server_s {
    int socket;
    sockaddr_in_t address;
    list_t clients;
    timeval_t timeout;
    game_t *game;
    // Client
    int (*accept_client)(game_server_t *server);
    bool (*read_client)(game_server_t *server, game_client_t *client);
    void (*disconnect_client)(game_server_t *server, game_client_t *client);
    // Select
    int (*select)(game_server_t *server, timeval_t *timeout);
    // Dtor
    void (*destroy)(game_server_t *server);
};

// Default structure of server
extern const game_server_t default_server;

// Server ctor and dtor
int server_init(game_server_t *server, int port);
void server_destroy(game_server_t *server);
// Select method
int server_select(game_server_t *server, timeval_t *timeout);
// Client-related methods
int server_accept_client(game_server_t *server);
bool server_read_client(game_server_t *server, game_client_t *client);
void server_disconnect_client(game_server_t *server, game_client_t *client);

// Game class
struct game_s {
    list_t events;
    map_t teams;
    game_map_t map;
    game_server_t server;
    int max_team_capacity;
    int frequency;
    // Events
    bool (*add_event)(game_t *game, void *params);
    bool (*remove_events)(game_t *game, game_event_type_t type,
        game_client_t *client);
    // Clients
    int (*add_client)(game_t *game, game_client_t *client, char *team_name);
    void (*remove_client)(game_t *game, game_client_t *client);
    // Run
    void (*run)(game_t *game);
    // Util
    void (*set_timeout)(game_t *game);
    long long int (*get_timeout)(game_t *game);
    game_client_t *(*get_player)(game_t *game, int id);
    void (*notify_all_graphic)(game_t *game, char *command,
        graphic_notification_params_t *params);
    // Dtor
    void (*destroy)(game_t *server);
};

// Default structure of game
extern const game_t default_game;

// Game ctor and dtor
int game_init(game_t *game, program_params_t *params);
void game_destroy(game_t *game);

// Run method
void game_run(game_t *game);

// Events methods
bool game_add_event(game_t *game, void *params);
bool game_remove_events(game_t *game, game_event_type_t type,
    game_client_t *client);

// Clients methods
int game_add_client(game_t *game, game_client_t *client, char *team_name);
void game_remove_client(game_t *game, game_client_t *client);

// Util methods
void game_set_timeout(game_t *game);
long long int game_get_timeout(game_t *game);
game_client_t *game_get_player(game_t *game, int id);
void game_notify_all_graphic(game_t *game, char *command,
    graphic_notification_params_t *params);

#endif
