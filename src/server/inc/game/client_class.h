/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - client class
*/

#ifndef ZAPPY_GAME_CLIENT_H_

    #define ZAPPY_GAME_CLIENT_H_

// Client class
typedef struct game_client_s {
    int socket;
    char *buffer;
    char *team_name;
    void (*destroy)(struct game_client_s *client);
} game_client_t;

// Client ctor, dtor and methods
int client_init(game_client_t *client, int socket);
void client_destroy(game_client_t *client);

#endif
