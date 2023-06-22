/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - notifications
*/

#include "zappy_misc.h"
#include "zappy_game.h"
#include "game/command_class.h"

// msz graphic notification
void graphic_notification_msz(game_server_t *server, game_client_t *client,
    ATTR_UNUSED graphic_notification_params_t *params)
{
    dprintf(client->socket, "msz %d %d\n", server->map.width,
        server->map.height);
}

// bct graphic notification
void graphic_notification_bct(game_server_t *server, game_client_t *client,
    graphic_notification_params_t *params)
{
    game_tile_t tile = server->map.tiles[params->y][params->x];

    dprintf(client->socket, "bct %d %d %d %d %d %d %d %d %d\n", params->x,
        params->y, tile.food, tile.linemate, tile.deraumere, tile.sibur,
        tile.mendiane, tile.phiras, tile.thystame);
}

// mct graphic notification
void graphic_notification_mct(game_server_t *server, game_client_t *client,
    ATTR_UNUSED graphic_notification_params_t *params)
{
    game_tile_t tile;

    for (int y = 0; y < server->map.height; y++) {
        for (int x = 0; x < server->map.width; x++) {
            tile = server->map.tiles[y][x];
            dprintf(client->socket, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
                tile.food, tile.linemate, tile.deraumere, tile.sibur,
                tile.mendiane, tile.phiras, tile.thystame);
        }
    }
}

// sgt graphic notification
void graphic_notification_sgt(game_server_t *server, game_client_t *client,
    ATTR_UNUSED graphic_notification_params_t *params)
{
    dprintf(client->socket, "sgt %d\n", server->frequency);
}
