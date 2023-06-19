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
int server_select(game_server_t *server)
{
    fd_set rfds;
    int max_rfd = readfds_init(&rfds, server);
    game_client_t *cli;
    int max_cli = MAX_CLIENTS;

    if (select(max_rfd + 1, &rfds, NULL, NULL, &server->timeout) < 0)
        return ERR_NETWORK;
    if (FD_ISSET(server->socket, &rfds) && server->clients.size < max_cli)
        handle_error(server->accept_client(server), error_client);
    for (int i = 0; i < server->clients.size;) {
        cli = server->clients.get(&server->clients, i);
        if (FD_ISSET(cli->socket, &rfds) && !server->read_client(server, cli))
            server->disconnect_client(server, cli);
        else
            i++;
    }
    return SUCCESS;
}
