/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - server class
*/

#include <unistd.h>
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
    .teams = {0},
    .map = {0},
    .clients = {0},
    .events = {0},
    .timeout = {
        .tv_sec = 0,
        .tv_usec = 0,
    },
    .frequency = 100,
    .max_team_capacity = 0,
    .destroy = &server_destroy,
    .select = &server_select,
    .run = &server_run,
    .add_event = &server_add_event,
    .remove_events = &server_remove_events,
    .get_player = &server_get_player,
    .accept_client = &server_accept_client,
    .read_client = &server_read_client,
    .disconnect_client = &server_disconnect_client,
    .set_timeout = &server_set_timeout,
    .get_timeout = &server_get_timeout,
    .notify_graphic = &server_notify_graphic,
    .init_client = &server_init_client,
};

// Initialize the teams of the server
static int teams_init(game_server_t *server, program_params_t *params)
{
    list_t *team;

    map_init(&server->teams, NULL, (void (*)(void *))&list_destroy, (int (*)
    (void *, void *))&strcmp);
    for (int i = 0; params->team_names[i]; i++) {
        team = malloc(sizeof(list_t));
        list_init(team, NULL, client_cmp_id);
        server->teams.set(&server->teams, strdup(params->team_names[i]), team);
    }
    return SUCCESS;
}

// Server constructor
int server_init(game_server_t *server, program_params_t *params)
{
    int status;
    *server = default_server;
    server->frequency = params->frequency;
    server->max_team_capacity = params->max_clients;
    server->address.sin_port = htons(params->port);
    if ((server->socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return ERR_SOCKET;
    if (bind(server->socket, (struct sockaddr *)&server->address, sizeof
    (server->address)) < 0 || listen(server->socket, MAX_CLIENTS) < 0)
        return ERR_BIND;
    list_init(&server->clients, (void (*)(void *))&client_destroy,
        client_cmp);
    list_init(&server->events, NULL, NULL);
    if ((status = game_map_init(&server->map, params->width,
        params->height))) {
        game_map_destroy(&server->map);
        return status;
    } else if ((status = teams_init(server, params)) != SUCCESS)
        return status;
    return SUCCESS;
}

// Server destructor
void server_destroy(game_server_t *server)
{
    if (server->teams.destroy)
        server->teams.destroy(&server->teams);
    if (server->map.destroy)
        server->map.destroy(&server->map);
    if (server->clients.destroy)
        server->clients.destroy(&server->clients);
    if (server->events.destroy)
        server->events.destroy(&server->events);
    if (server->socket >= 0)
        close(server->socket);
}
