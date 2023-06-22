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
typedef struct graphic_notification_params_s graphic_notification_params_t;

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
    void (*notify_all_graphic)(game_server_t *server, char *command,
        graphic_notification_params_t *params);
    // Dtor
    void (*destroy)(game_server_t *server);
};

// Default structure of server
extern const game_server_t default_server;

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
void server_notify_all_graphic(game_server_t *server, char *command,
    graphic_notification_params_t *params);
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

// Graphic notification params structure
typedef struct graphic_notification_params_s {
    int id;
    int x;
    int y;
    int egg_id;
    game_resource_t resource;
    char *message;
    bool success;
    game_direction_t direction;
    char *team_name;
    int level;
} graphic_notification_params_t;

// Default structure of graphic notification params
extern const graphic_notification_params_t default_graphic_notification_params;

// Graphic notifications
void graphic_notification_msz(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_bct(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_mct(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_tna(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_ppo(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_plv(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_pin(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_sgt(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_pnw(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_pex(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
/*void graphic_notification_pbc(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_pic(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_pie(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);*/
void graphic_notification_pfk(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_pdr(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_pgt(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_pdi(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_enw(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_eht(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_ebo(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_edi(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_seg(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_smg(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_suc(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_sbp(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params);

// Graphic notifications table

typedef struct graphic_notification_s {
    char *command;
    void (*function)(game_server_t *server, game_client_t *client,
        graphic_notification_params_t *params);
} graphic_notification_t;

typedef struct graphic_notification_pair_s {
    graphic_notification_params_t params;
    char command[4];
} graphic_notification_pair_t;

extern const graphic_notification_t graphic_notifications_table[];

#endif
