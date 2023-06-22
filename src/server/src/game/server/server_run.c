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

// Main loop of the server
int server_run(game_server_t *server)
{
    int status;
    event_params_t params = {tick(), REFILL_TIME * 1e6, MAP_REFILL, NULL};
    game_event_t *event;

    server->add_event(server, &params);
    do {
        if (server->get_timeout(server) <= 0 && server->events.size > 0) {
            event = server->events.get(&server->events, 0);
            events_table[event->type](server, event->client);
            server->events.remove(&server->events, 0);
            server->set_timeout(server);
        }
        if (server->events.size == 0)
            server->set_timeout(server);
        if ((status = server->select(server)) != SUCCESS)
            return status;
    } while (true);
    return SUCCESS;
}
