/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side : run method
*/

#include "zappy_misc.h"
#include "zappy_game.h"
#include "game/event_class.h"

static const char *error_network = "Select failed";

// Main loop of the game
void game_run(game_t *game)
{
    event_params_t params = {tick(), REFILL_TIME * 1e6, MAP_REFILL, NULL};
    game_event_t *event;
    game_server_t *server = &game->server;

    game->add_event(game, &params);
    do {
        if (game->get_timeout(game) <= 0 && game->events.size > 0) {
            event = game->events.get(&game->events, 0);
            events_table[event->type](game, event->client);
            game->events.remove(&game->events, 0);
            game->set_timeout(game);
        }
        if (game->events.size > 0 && !handle_error(server->select(server,
            &server->timeout), error_network))
            break;
        if (game->events.size == 0 && !handle_error(server->select(server,
            NULL), error_network))
            break;
    } while (true);
}

// A variant that doesn't use the timeout
void game_run_no_timeout(game_t *game)
{
    event_params_t params = {tick(), REFILL_TIME * 1e6, MAP_REFILL, NULL};
    game_event_t *event;
    game_server_t *server = &game->server;

    game->add_event(game, &params);
    do {
        for (int i = 0; i < EVENT_TYPE_COUNT; i++) {
            event = game->events.get(&game->events, i);
            events_table[event->type](game, event->client);
        }
        if (!handle_error(server->select(server, NULL), error_network))
            break;
    } while (true);
}
