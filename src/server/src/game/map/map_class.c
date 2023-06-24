/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** map
*/

#include "game/map_class.h"
#include "zappy_misc.h"

// Initial structure of map
static const game_map_t default_map = {
    .width = 0,
    .height = 0,
    .tiles = NULL,
    .total_food = 0,
    .total_linemate = 0,
    .total_deraumere = 0,
    .total_sibur = 0,
    .total_mendiane = 0,
    .total_phiras = 0,
    .total_thystame = 0,
    .last_refill = 0,
    .refill = &map_refill,
    .destroy = &game_map_destroy,
};

// Map constructor
int game_map_init(game_map_t *map, int width, int height)
{
    *map = default_map;
    map->width = width;
    map->height = height;
    if (!(map->tiles = malloc(sizeof(game_tile_t *) * height)))
        return ERR_ALLOC;
    for (int i = 0; i < height; i++) {
        if (!(map->tiles[i] = malloc(sizeof(game_tile_t) * width)))
            return ERR_ALLOC;
        for (int j = 0; j < width; j++)
            tile_init(&map->tiles[i][j]);
    }
    return SUCCESS;
}

// Map destructor
void game_map_destroy(game_map_t *map)
{
    for (int i = 0; i < map->height; i++) {
        for (int j = 0; j < map->width; j++)
            map->tiles[i][j].destroy(&map->tiles[i][j]);
        free(map->tiles[i]);
        *(map->tiles + i) = NULL;
    }
    free(map->tiles);
}
