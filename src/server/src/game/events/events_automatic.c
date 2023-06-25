/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Events
*/

#include "zappy_misc.h"
#include "game/server_class.h"
#include "zappy_game.h"
#include "game/command_class.h"
#include "game/notification_class.h"
#include "game/event_class.h"

// Updates the player's health, returns false if dead
void event_remove_player_health(game_t *game, game_client_t *client)
{
    long long int now = tick();
    event_params_t params = {now, FOOD_TIME * 1e6,
        PLAYER_REMOVE_HEALTH, client};

    if (now - client->last_fed < FOOD_TIME * 1e6 / game->frequency)
        return;
    if (client->inventory[FOOD] <= 0) {
        dprintf(client->socket, "dead\n");
        game->remove_client(game, client);
        game->server.disconnect_client(&game->server, client);
    } else {
        client->inventory[FOOD]--;
        game->add_event(game, &params);
    }
}

// Refills the map and adds a refill event
void event_refill(game_t *game, ATTR_UNUSED game_client_t *client)
{
    long long int now = tick();
    event_params_t e_params = {now, REFILL_TIME * 1e6, MAP_REFILL, NULL};
    graphic_notification_params_t params = default_graphic_notification_params;

    if (game->map.refill(&game->map))
        game->notify_all_graphic(game, "mct", &params);
    game->add_event(game, &e_params);
}
