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

static const int directions[][3] = {
    {0, -1, 1},
    {-1, -1, 2},
    {-1, 0, 3},
    {-1, 1, 4},
    {0, 1, 5},
    {1, 1, 6},
    {1, 0, 7},
    {1, -1, 8}
};

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

int game_get_direction_from_broadcast(game_t *game, game_client_t *cfrom,
    game_client_t *cto)
{
    int x1 = cto->x - cfrom->x;
    int x2 = game->map.width - ABS(x1);
    int y1 = cto->y - cfrom->y;
    int y2 = game->map.height - ABS(y1);
    int x = cfrom->x < cto->x ? 1 : cfrom->x > cto->x ? -1 : 0;
    int y = cfrom->y < cto->y ? 1 : cfrom->y > cto->y ? -1 : 0;
    int orientation = 0;

    if (ABS(x2) < ABS(x1))
        x *= (-1);
    if (ABS(y2) < ABS(y1))
        y *= (-1);
    for (int i = 0; i < 8; i++)
        if (directions[i][0] == x && directions[i][1] == y)
            orientation = directions[i][2];
    return orientation - (int)(cfrom->direction * 2);
}
