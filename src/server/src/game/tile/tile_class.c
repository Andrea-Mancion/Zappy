/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** tile
*/

#include "game/tile_class.h"
#include "zappy_misc.h"

// Initial structure of tile
static const game_tile_t default_tile = {
    .food = 0,
    .linemate = 0,
    .deraumere = 0,
    .sibur = 0,
    .mendiane = 0,
    .phiras = 0,
    .thystame = 0,
    .players = {0},
    .destroy = &tile_destroy,
};

// Tile constructor
int tile_init(game_tile_t *tile)
{
    int status;

    *tile = default_tile;
    if ((status = list_init(&tile->players)) != SUCCESS)
        return status;
    return SUCCESS;
}

// Tile destructor
void tile_destroy(game_tile_t *tile)
{
    tile->players.destroy(&tile->players);
}
