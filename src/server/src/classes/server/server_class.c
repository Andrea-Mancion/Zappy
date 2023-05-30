/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - server class
*/

#include <unistd.h>
#include "zappy_server.h"
#include "classes/server_class.h"

// Initial structure of server
static const server_t default_server = {
    .socket = -1,
    .address = {
        .sin_family = AF_INET,
        .sin_addr = {
            .s_addr = INADDR_ANY,
        },
        .sin_port = 0,
    },
    .timeout = {
        .tv_sec = 20,
        .tv_usec = 0,
    },
    .client_list = {0},
    .command_table = command_table,
    .destroy = &server_destroy,
    .read_from_client = &server_read_from_client,
    .run = &server_run,
};

// Server constructor
int server_init(server_t *server, params_t *params)
{
    *server = default_server;
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket == -1)
        return ERR_SOCKET;
    server->address.sin_port = htons(params->port);
    list_init(&server->client_list);
    if (bind(server->socket, (struct sockaddr *)&server->address, sizeof(
        server->address)) < 0 || listen(server->socket, MAX_CLIENTS) < 0)
        return ERR_BIND;
    return SUCCESS;
}

// Server destructor
void server_destroy(server_t *server)
{
    client_t *client;

    for (int i = 0; i < server->client_list.size; i++) {
        client = server->client_list.get(&server->client_list, i);
        client->destroy(client);
        free(client);
    }
    server->client_list.destroy(&server->client_list);
    if (server->socket >= 0)
        close(server->socket);
}
