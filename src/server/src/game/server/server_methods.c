/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - server methods
*/

#include "zappy_misc.h"
#include "game/server_class.h"
#include "game/client_class.h"
#include "game/event_class.h"

// Get client from player id
game_client_t *server_get_player(game_server_t *server, int id)
{
    game_client_t *client;

    for (int i = 0; i < server->clients.size; i++) {
        client = server->clients.get(&server->clients, i);
        if (client->id == id)
            return client;
    }
    return NULL;
}

// Sets the timeout to the next event
void server_set_timeout(game_server_t *server)
{
    game_event_t *event;
    long long int time;

    if (server->events.size == 0)
        server->timeout = (struct timeval){86400, 0};
    else {
        event = server->events.get(&server->events, 0);
        time = event->time - tick();
        time = time < 0 ? 0 : time;
        server->timeout.tv_sec = time / 1e6;
        server->timeout.tv_usec = time % (long long int)1e6;
    }
}

// Returns the server timeout in microseconds
long long int server_get_timeout(game_server_t *server)
{
    return server->timeout.tv_sec * 1e6 + server->timeout.tv_usec;
}
