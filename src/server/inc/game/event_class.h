/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - game namespace
*/

#ifndef ZAPPY_GAME_EVENTS_H_

    #define ZAPPY_GAME_EVENTS_H_

    #include "zappy_game.h"
    #include "game/server_class.h"
    #include "game/client_class.h"

// Event params structure
typedef struct event_params_s {
    long long int start_time;
    long long int duration;
    game_event_type_t type;
    game_client_t *client;
} event_params_t;

// Event structure
typedef struct game_event_s {
    long long int time;
    game_event_type_t type;
    game_client_t *client;
} game_event_t;

// Global variables

// Functions
void event_start_command(game_server_t *server, game_client_t *client);
void event_end_command(game_server_t *server, game_client_t *client);
void event_remove_player_health(game_server_t *server, game_client_t *client);
void event_refill(game_server_t *server);

#endif
