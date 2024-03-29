/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - client class
*/

#ifndef ZAPPY_GAME_CLIENT_H_

    #define ZAPPY_GAME_CLIENT_H_

    #include "zappy_game.h"
    #include "misc/list_class.h"

// Client command structure
typedef struct pending_command_s {
    char *input;
    long long int received_at;
    int duration;
    char *output;
    char *broadcast;
    list_t graphic_notifications;
    void (*destroy)(struct pending_command_s *command);
} pending_command_t;

// Default structure of pending command
extern const pending_command_t default_pending_command;

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
    int level;
    int inventory[RESOURCE_COUNT];
    long long int last_fed;
    void (*destroy)(struct game_client_s *client);
} game_client_t;


// Default structure of client
extern const game_client_t default_client;

// Client ctor, dtor and methods
int client_init(game_client_t *client, int socket);
void client_destroy(game_client_t *client);

// Other functions
int client_cmp(void *a, void *b);
int client_cmp_id(void *a, void *b);

#endif
