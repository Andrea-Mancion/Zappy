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

static void handle_event(game_server_t *server, game_event_t *event)
{
    if (event->type == MAP_REFILL)
        event_refill(server);
    if (event->type == PLAYER_COMMAND)
        event_end_command(server, event->client);
    if (event->type == PLAYER_REMOVE_HEALTH)
        event_remove_player_health(server, event->client);
}

// Checks if an event is ready to be handled
static void check_event(game_server_t *server)
{
    if (server->events.size == 0)
        return server->set_timeout(server);
    handle_event(server, server->events.get(&server->events, 0));
    server->events.remove(&server->events, 0);
    server->set_timeout(server);
}

// Main loop of the server
int server_run(game_server_t *server)
{
    int status;
    event_params_t params = {tick(), REFILL_TIME * 1e6, MAP_REFILL, NULL};

    server->add_event(server, &params);
    do {
        if (server->get_timeout(server) <= 0)
            check_event(server);
        if ((status = server->select(server)) != SUCCESS)
            return status;
    } while (true);
    return SUCCESS;
}
