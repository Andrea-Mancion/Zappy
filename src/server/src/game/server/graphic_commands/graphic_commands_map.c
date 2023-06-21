/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - commands
*/

#include "zappy_misc.h"
#include "zappy_game.h"
#include "game/command_class.h"

// msz graphic command
int graphic_command_msz(game_server_t *server, game_client_t *client,
    char **args)
{
    if (args[0]) {
        dprintf(client->socket, "sbp\n");
        return ERR_COMMAND;
    }
    dprintf(client->socket, "msz %d %d\n", server->map.width,
        server->map.height);
    return SUCCESS;
}

// bct graphic command
int graphic_command_bct(game_server_t *server, game_client_t *client,
    char **args)
{
    game_tile_t tile;
    int x;
    int y;

    if (!args[0] || !args[1] || args[2]) {
        dprintf(client->socket, "sbp\n");
        return ERR_COMMAND;
    }
    x = atoi(args[0]);
    y = atoi(args[1]);
    if (x < 0 || x >= server->map.width || y < 0 || y >= server->map.height) {
        dprintf(client->socket, "sbp\n");
        return ERR_COMMAND;
    }
    tile = server->map.tiles[x][y];
    dprintf(client->socket, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
        tile.food, tile.linemate, tile.deraumere, tile.sibur, tile.mendiane,
        tile.phiras, tile.thystame);
    return SUCCESS;
}

// mct graphic command
int graphic_command_mct(game_server_t *server, game_client_t *client,
    char **args)
{
    game_tile_t tile;

    if (args[0]) {
        dprintf(client->socket, "sbp\n");
        return ERR_COMMAND;
    }
    for (int y = 0; y < server->map.height; y++) {
        for (int x = 0; x < server->map.width; x++) {
            tile = server->map.tiles[y][x];
            dprintf(client->socket, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
                tile.food, tile.linemate, tile.deraumere, tile.sibur,
                tile.mendiane, tile.phiras, tile.thystame);
        }
    }
    return SUCCESS;
}

// sst graphic command
int graphic_command_sst(game_server_t *server, game_client_t *client,
    char **args)
{
    int frequency;

    if (!args[0] || args[1]) {
        dprintf(client->socket, "sbp\n");
        return ERR_COMMAND;
    }
    frequency = atoi(args[0]);
    if (frequency < 2 || frequency > 10000) {
        dprintf(client->socket, "sbp\n");
        return ERR_COMMAND;
    }
    server->frequency = frequency;
    dprintf(client->socket, "sst %d\n", server->frequency);
    return SUCCESS;
}
