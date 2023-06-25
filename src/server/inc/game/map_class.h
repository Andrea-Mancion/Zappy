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
    long long int last_refill;
    bool (*refill)(struct game_map_s *map);
    int *(*get_resource_address)(struct game_map_s *map,
        game_resource_t resource);
    void (*destroy)(struct game_map_s *map);
} game_map_t;

// Default structure of map
extern const game_map_t default_game_map;

// Map ctor, dtor and methods
int game_map_init(game_map_t *map, int width, int height);
void game_map_destroy(game_map_t *map);
bool map_refill(game_map_t *map);
int *map_get_resource_address(game_map_t *map, game_resource_t resource);

#endif
