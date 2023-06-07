/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - tile class
*/

#ifndef ZAPPY_GAME_TILE_H_

    #define ZAPPY_GAME_TILE_H_

    #include "misc/list_class.h"

// Tile class
typedef struct game_tile_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
    list_t players;
    void (*destroy)(struct game_tile_s *tile);
} game_tile_t;

// Tile ctor, dtor and methods
int tile_init(game_tile_t *tile);
void tile_destroy(game_tile_t *tile);

#endif
