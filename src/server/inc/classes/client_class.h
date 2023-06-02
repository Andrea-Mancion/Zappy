/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - client class
*/

#ifndef CLIENT_CLASS_H

    #define CLIENT_CLASS_H

    #include "zappy_server.h"

// Client class
typedef struct client_s {
    int socket;
    char *buffer;
    char *team_name;
    void (*destroy)(struct client_s *client);
} client_t;

// Client ctor, dtor and methods
int client_init(client_t *client, int socket);
void client_destroy(client_t *client);

#endif
