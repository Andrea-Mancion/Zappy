/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side : run method
*/

#include "zappy_misc.h"
#include "game/server_class.h"
#include "zappy_game.h"
#include "game/event_class.h"

// Sets a new timeout if the given timeout is lower than the current one
bool server_add_event(game_server_t *server, void *void_params)
{
    event_params_t *params = (event_params_t *)void_params;
    game_event_t *event = malloc(sizeof(game_event_t));
    long long int will_happen_at = params->start_time +
        (params->duration / server->frequency);
    bool success = false;

    if (!event)
        return false;
    *event = (game_event_t){will_happen_at, params->type, params->client};
    for (int i = 0; i < server->events.size; i++)
        if (((game_event_t *)server->events.get(&server->events, i))->time
            > will_happen_at) {
            success = server->events.insert(&server->events, event, i);
            server->set_timeout(server);
            return success;
        }
    success = server->events.add(&server->events, event);
    server->set_timeout(server);
    return success;
}

bool server_remove_events(game_server_t *server, game_event_type_t type,
    game_client_t *client)
{
    game_event_t *event;
    bool found = false;

    for (int i = 0; i < server->events.size; i++) {
        event = server->events.get(&server->events, i);
        if (event->type == type && event->client == client) {
            server->events.remove(&server->events, i);
            found = true;
        }
    }
    if (found)
        server->set_timeout(server);
    return found;
}
