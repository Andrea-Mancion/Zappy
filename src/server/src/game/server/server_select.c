/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - server class
*/

#include "zappy_misc.h"
#include "game/client_class.h"
#include "game/map_class.h"
#include "misc/list_class.h"
#include "game/server_class.h"

static const char *error_client = "Couldn't accept client";

// Initializes the readfds and returns the max fd found
static int readfds_init(fd_set *readfds, game_server_t *server)
{
    int max_fd = server->socket;
    game_client_t *client;

    FD_ZERO(readfds);
    FD_SET(server->socket, readfds);
    for (int i = 0; i < server->clients.size; i++) {
        client = server->clients.get(&server->clients, i);
        if (client->socket >= 0) {
            FD_SET(client->socket, readfds);}
        if (client->socket > max_fd)
            max_fd = client->socket;
    }
    return max_fd;
}

// Manages clients arrival, departure and input
int server_select(game_server_t *server, timeval_t *timeout)
{
    fd_set rfds;
    game_client_t *cl;
    int max_rfd = readfds_init(&rfds, server);
    int max_cl = MAX_CLIENTS;

    if (select(max_rfd + 1, &rfds, NULL, NULL, timeout) < 0)
        return ERR_NETWORK;
    if (FD_ISSET(server->socket, &rfds) && server->clients.size < max_cl)
        handle_error(server->accept_client(server), error_client);
    for (int i = 0; i < server->clients.size;) {
        cl = server->clients.get(&server->clients, i);
        if (FD_ISSET(cl->socket, &rfds) && !server->read_client(server, cl)) {
            server->game->remove_client(server->game, cl);
            server->disconnect_client(server, cl);
        } else
            i++;
    }
    return SUCCESS;
}
