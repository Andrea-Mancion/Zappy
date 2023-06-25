/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - server class
*/

#include "zappy_misc.h"
#include "game/server_class.h"
#include "game/client_class.h"

// Initial structure of server
const game_server_t default_server = {
    .socket = -1,
    .address = {
        .sin_family = AF_INET,
        .sin_addr = {
            .s_addr = INADDR_ANY,
        },
        .sin_port = 0,
    },
    .clients = {0},
    .timeout = {
        .tv_sec = 0,
        .tv_usec = 0,
    },
    .game = NULL,
    .destroy = &server_destroy,
    .select = &server_select,
    .accept_client = &server_accept_client,
    .read_client = &server_read_client,
    .disconnect_client = &server_disconnect_client,
};

// Server constructor
int server_init(game_server_t *server, int port)
{
    *server = default_server;
    server->address.sin_port = htons(port);
    if ((server->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return ERR_SOCKET;
    if (bind(server->socket, (struct sockaddr *)&server->address, sizeof
    (server->address)) < 0 || listen(server->socket, MAX_CLIENTS) < 0)
        return ERR_BIND;
    list_init(&server->clients, (void (*)(void *))&client_destroy, client_cmp);
    return SUCCESS;
}

// Server destructor
void server_destroy(game_server_t *server)
{
    if (server->clients.destroy)
        server->clients.destroy(&server->clients);
    if (server->socket >= 0)
        close(server->socket);
}
