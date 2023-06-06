/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - server class
*/

#include <unistd.h>
#include "zappy_misc.h"
#include "game/server_class.h"

// Initial structure of server
static const game_server_t default_server = {
    .socket = -1,
    .address = {
        .sin_family = AF_INET,
        .sin_addr = {
            .s_addr = INADDR_ANY,
        },
        .sin_port = 0,
    },
    .timeout = {
        .tv_sec = 10,
        .tv_usec = 0,
    },
    .timer = {0},
    .map = {0},
    .client_list = {0},
    .command_table = command_table,
    .destroy = &server_destroy,
    .read_from_client = &server_read_from_client,
    .run = &server_run,
};

// Server constructor
int server_init(game_server_t *server, program_params_t *params)
{
    int status;

    *server = default_server;
    server->socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket < 0)
        return ERR_SOCKET;
    server->address.sin_port = htons(params->port);
    if ((status = list_init(&server->client_list)) != SUCCESS)
        return status;
    if (bind(server->socket, (struct sockaddr *)&server->address, sizeof(
        server->address)) < 0 || listen(server->socket, MAX_CLIENTS) < 0)
        return ERR_BIND;
    if ((status = map_init(&server->map, params->width, params->height)))
        return status;
    if ((status = timer_init(&server->timer, params->frequency)))
        return status;
    server->timer.start(&server->timer);
    return SUCCESS;
}

// Server destructor
void server_destroy(game_server_t *server)
{
    game_client_t *client;

    for (int i = 0; i < server->client_list.size; i++) {
        client = server->client_list.get(&server->client_list, i);
        client->destroy(client);
        free(client);
    }
    server->client_list.destroy(&server->client_list);
    map_destroy(&server->map);
    if (server->socket >= 0)
        close(server->socket);
}
