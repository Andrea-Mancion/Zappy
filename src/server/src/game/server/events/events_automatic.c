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
#include "game/event_class.h"

// Updates the player's health, returns false if dead
void event_remove_player_health(game_server_t *server, game_client_t *client)
{
    event_params_t params = {tick(), FOOD_TIME * 1e6,
        PLAYER_REMOVE_HEALTH, client};

    if (client->inventory[FOOD] <= 0) {
        dprintf(client->socket, "dead\n");
        server->disconnect_client(server, client);
        return;
    }
    client->inventory[FOOD]--;
    server->add_event(server, &params);
}

// Refills the map and adds a refill event
void event_refill(game_server_t *server, ATTR_UNUSED game_client_t *client)
{
    event_params_t params = {tick(), REFILL_TIME * 1e6, MAP_REFILL, NULL};

    server->map.refill(&server->map);
    server->add_event(server, &params);
}
