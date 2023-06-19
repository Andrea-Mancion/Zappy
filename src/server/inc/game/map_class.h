/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - map class
*/

#ifndef ZAPPY_GAME_MAP_H_

    #define ZAPPY_GAME_MAP_H_

    #include "zappy_game.h"
    #include "game/tile_class.h"

// Resource densities array
    #define RESOURCE_DENSITIES (double[RESOURCE_COUNT]) { \
        FOOD_DENSITY, \
        LINEMATE_DENSITY, \
        DERAUMERE_DENSITY, \
        SIBUR_DENSITY, \
        MENDIANE_DENSITY, \
        PHIRAS_DENSITY, \
        THYSTAME_DENSITY \
    }

// Map class
typedef struct game_map_s {
    int width;
    int height;
    game_tile_t **tiles;
    int total_food;
    int total_linemate;
    int total_deraumere;
    int total_sibur;
    int total_mendiane;
    int total_phiras;
    int total_thystame;
    void (*refill)(struct game_map_s *map);
    void (*destroy)(struct game_map_s *map);
} game_map_t;

// Map ctor, dtor and methods
int game_map_init(game_map_t *map, int width, int height);
void game_map_destroy(game_map_t *map);
void map_refill(game_map_t *map);

#endif
