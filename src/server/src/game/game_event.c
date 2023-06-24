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
bool game_add_event(game_t *game, void *vparams)
{
    event_params_t *params = vparams;
    game_event_t *event = malloc(sizeof(game_event_t));
    long long int will_happen_at = params->start_time +
        (params->duration / game->frequency);
    bool success = false;

    if (!event)
        return false;
    *event = (game_event_t){will_happen_at, params->type, params->client};
    for (int i = 0; i < game->events.size; i++)
        if (((game_event_t *)game->events.get(&game->events, i))->time
            > will_happen_at) {
            success = game->events.insert(&game->events, event, i);
            game->set_timeout(game);
            return success;
        }
    success = game->events.add(&game->events, event);
    game->set_timeout(game);
    return success;
}

bool game_remove_events(game_t *game, game_event_type_t type,
    game_client_t *client)
{
    game_event_t *event;
    bool found = false;

    for (int i = 0; i < game->events.size; i++) {
        event = game->events.get(&game->events, i);
        if (event->type == type && event->client == client) {
            game->events.remove(&game->events, i);
            found = true;
        }
    }
    if (found)
        game->set_timeout(game);
    return found;
}
