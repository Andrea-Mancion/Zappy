/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - client class
*/

#ifndef ZAPPY_GAME_CLIENT_H_

    #define ZAPPY_GAME_CLIENT_H_

    #include "zappy_game.h"
    #include "game/map_class.h"

// Client command structure
typedef struct pending_command_s {
    char *input;
    long long int received_at;// in microseconds
    int duration;// in seconds
    char *output;
    void (*destroy)(struct pending_command_s *command);
} pending_command_t;

// Client command ctor, dtor and methods
int pending_command_init(pending_command_t *command, char *input);
void pending_command_destroy(pending_command_t *command);

// Client class
typedef struct game_client_s {
    int socket;
    char *buffer;
    list_t commands;
    char *team_name;
    int id;
    game_direction_t direction;
    int x;
    int y;
    int life_units;
    int level;
    int inventory[RESOURCE_COUNT];
    void (*destroy)(struct game_client_s *client);
} game_client_t;

// Client ctor, dtor and methods
int client_init(game_client_t *client, int socket);
void client_destroy(game_client_t *client);
void client_init_as_ai(game_client_t *client, game_map_t *map);

// Other functions
int client_cmp(void *a, void *b);

#endif
