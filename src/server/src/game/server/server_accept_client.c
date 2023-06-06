/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - server class
*/

#include "zappy_misc.h"
#include "game/client_class.h"
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
    for (int i = 0; i < server->client_list.size; i++) {
        client = server->client_list.get(&server->client_list, i);
        if (client->socket >= 0) {
            FD_SET(client->socket, readfds);}
        if (client->socket > max_fd)
            max_fd = client->socket;
    }
    return max_fd;
}

// Creates a new client and adds it to the client list
static int server_accept_client(game_server_t *server)
{
    game_client_t *client = malloc(sizeof(game_client_t));
    int socket;
    int init_return;

    if (!client)
        return ERR_ALLOC;
    if ((socket = accept(server->socket, NULL, NULL)) < 0) {
        free(client);
        return ERR_SOCKET;
    }
    if ((init_return = client_init(client, socket)) != SUCCESS) {
        client->destroy(client);
        free(client);
        return init_return;
    } else if (!server->client_list.add(&server->client_list, client)) {
        client->destroy(client);
        free(client);
        return ERR_ALLOC;
    }
    return SUCCESS;
}

// Disconnects a client, removes it from the list and destroys it
static void server_disconnect_client(game_server_t *server,
    game_client_t *client, int index)
{
    server->client_list.remove(&server->client_list, index);
    client->destroy(client);
    free(client);
}

// Scans all client sockets with select, returns false if an error occured
int server_run(game_server_t *server)
{
    fd_set readfds;
    int max_fd = readfds_init(&readfds, server);
    game_client_t *client;

    if (select(max_fd + 1, &readfds, NULL, NULL, &server->timeout) < 0)
        return ERR_NETWORK;
    if (FD_ISSET(server->socket, &readfds)
        && server->client_list.size < MAX_CLIENTS)
        HANDLE_ERROR(server_accept_client(server), error_client);
    for (int i = 0; i < server->client_list.size; i++) {
        client = server->client_list.get(&server->client_list, i);
        if (!FD_ISSET(client->socket, &readfds))
            continue;
        if (server_read_from_client(server, client) == false)
            server_disconnect_client(server, client, i);
    }
    return SUCCESS;
}
