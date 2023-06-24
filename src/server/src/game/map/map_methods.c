/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - server class
*/

#include "game/map_class.h"

// Function that spawns a given resource on a random tile of the map
static void map_spawn_resource(game_map_t *map, game_resource_t resource)
{
    int x = rand() % map->width;
    int y = rand() % map->height;
    int *resources_address[] = {&map->tiles[y][x].food,
        &map->tiles[y][x].linemate, &map->tiles[y][x].deraumere,
        &map->tiles[y][x].sibur, &map->tiles[y][x].mendiane,
        &map->tiles[y][x].phiras, &map->tiles[y][x].thystame};
    int *total_resources_address[] = {&map->total_food, &map->total_linemate,
    &map->total_deraumere, &map->total_sibur, &map->total_mendiane,
    &map->total_phiras, &map->total_thystame};

    *resources_address[resource] += 1;
    *total_resources_address[resource] += 1;
}

// Function that refills the map with the correct amount of resources
void map_refill(game_map_t *map)
{
    int total_tiles = map->width * map->height;
    int *total_resources[] = {&map->total_food, &map->total_linemate,
    &map->total_deraumere, &map->total_sibur, &map->total_mendiane,
    &map->total_phiras, &map->total_thystame};

    for (int i = 0; i < RESOURCE_COUNT; i++) {
        for (int j = *total_resources[i];
            j < total_tiles * resource_quantities[i]; j++)
            map_spawn_resource(map, i);
    }
    map->last_refill = tick();
}
