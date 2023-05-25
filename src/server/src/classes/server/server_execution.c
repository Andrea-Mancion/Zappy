/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - server class
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zappy_server.h"
#include "classes/server_class.h"

static int readfds_init(fd_set *readfds, server_t *server)
{
    int max_fd = server->socket;

    FD_ZERO(readfds);
    FD_SET(server->socket, readfds);
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->client_list[i] > 0)
            FD_SET(server->client_list[i], readfds);
        if (server->client_list[i] > max_fd)
            max_fd = server->client_list[i];
    }
    return max_fd;
}

bool server_run(server_t *server)
{
    fd_set readfds;
    int max_fd = readfds_init(&readfds, server);

    if (select(max_fd + 1, &readfds, NULL, NULL, &server->timeout) <= 0)
        return false;
    if (FD_ISSET(server->socket, &readfds)) {
        // TODO: créer et init le client avec accept (dans une autre fonction)
        // TODO: ajouter le client à la liste (dans une autre fonction)
    }
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (!FD_ISSET(server->client_list[i], &readfds))
            continue;
        if (!server_read_from_client(server, server->client_list[i])) {
            // TODO: remove le client de la liste (dans une autre fonction)
            // TODO: destroy le client (dans une autre fonction)
        }
    }
    return true;
}
