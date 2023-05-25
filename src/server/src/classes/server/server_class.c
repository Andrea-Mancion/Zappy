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

static const server_t default_server = {
    .socket = -1,
    .address = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = 0,
    },
    .timeout = {
        .tv_sec = 20,
        .tv_usec = 0,
    },
    .client_list = NULL,
    .destroy = &server_destroy,
    .read_from_client = &server_read_from_client,
    .run = &server_run,
};

void server_init(server_t *server, params_t *params)
{
    *server = default_server;
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket == -1)
        return;
    server->address.sin_port = htons(params->port);
    server->client_list = malloc(sizeof(int) * MAX_CLIENTS);
    memset(server->client_list, -1, sizeof(int) * MAX_CLIENTS);
    if (bind(server->socket, (struct sockaddr *)&server->address, sizeof(
        server->address)) < 0 || listen(server->socket, MAX_CLIENTS) < 0) {
        close(server->socket);
        server->socket = -1;
    }
}

void server_destroy(server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->client_list[i] > 0)
            close(server->client_list[i]);
    }
    free(server->client_list);
    if (server->socket == -1)
        return;
    close(server->socket);
}
