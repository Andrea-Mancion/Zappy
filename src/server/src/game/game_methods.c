/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - game methods
*/

#include "zappy_misc.h"
#include "game/client_class.h"
#include "game/event_class.h"
#include "game/notification_class.h"

// Get client from player id
game_client_t *game_get_player(game_t *game, int id)
{
    game_client_t *client;

    for (int i = 0; i < game->server.clients.size; i++) {
        client = game->server.clients.get(&game->server.clients, i);
        if (client->id == id)
            return client;
    }
    return NULL;
}

// Sets the timeout to the next event
void game_set_timeout(game_t *game)
{
    game_event_t *event = game->events.get(&game->events, 0);
    long long int time;

    if (!event) {
        game->server.timeout = (struct timeval){0, 0};
        return;
    }
    time = event->time - tick();
    time = time < 0 ? 0 : time;
    game->server.timeout = (struct timeval){time / 1e6, time % (long long int)
        1e6};
}

// Returns the game timeout in microseconds
long long int game_get_timeout(game_t *game)
{
    return game->server.timeout.tv_sec * 1e6 + game->server.timeout.tv_usec;
}

// Notifies all graphical clients of a new event
void game_notify_all_graphic(game_t *game, char *command,
    graphic_notification_params_t *params)
{
    game_client_t *client;
    const graphic_notification_t *graphic_notification = NULL;

    for (int i = 0; graphic_notifications_table[i].command; i++) {
        if (strcmp(graphic_notifications_table[i].command, command) == 0) {
            graphic_notification = &graphic_notifications_table[i];
            break;
        }
    }
    if (!graphic_notification) {
        printf("Unknown graphic notification: %s\n", command);
        return;
    }
    for (int i = 0; i < game->server.clients.size; i++) {
        client = game->server.clients.get(&game->server.clients, i);
        if (client->team_name && strcmp(client->team_name, "GRAPHIC") == 0)
            graphic_notification->function(game, client, params);
    }
}
