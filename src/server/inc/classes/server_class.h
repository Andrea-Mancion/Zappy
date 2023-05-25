/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - server class
*/

#ifndef SERVER_CLASS_H

    #define SERVER_CLASS_H

    #include "zappy_server.h"
    #include "classes/params_class.h"

typedef struct server_s {
    int socket;
    struct sockaddr_in address;
    struct timeval timeout;
    int *client_list;// TODO: remplacer int par une classe client
    void (*destroy)(struct server_s *server);
    bool (*read_from_client)(struct server_s *server, int client_fd);
    bool (*run)(struct server_s *server);
} server_t;

void server_init(server_t *server, params_t *params);
bool server_run(server_t *server);
bool server_read_from_client(server_t *server, int client_fd);
void server_destroy(server_t *server);

#endif
