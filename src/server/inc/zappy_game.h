/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - game namespace
*/

#ifndef ZAPPY_GAME_H_

    #define ZAPPY_GAME_H_

    #include "zappy_misc.h"

// Settings
    #define MAX_CLIENTS 100
    #define BUFFER_SIZE 1024
    #define MAX_PENDING_COMMANDS 10
    #define REFILL_TIME 20
    #define FOOD_TIME 126
    #define MAX_LEVEL 8

// Resources enum
typedef enum game_resource_e {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    RESOURCE_COUNT
} game_resource_t;

// Resources names array
extern const char *resource_names[];

// Resources quantities array
extern const double resource_quantities[];

// Direction enum
typedef enum game_direction_e {
    NORTH,
    EAST,
    SOUTH,
    WEST,
    DIRECTION_COUNT
} game_direction_t;

// Event type enum
typedef enum game_event_type_e {
    MAP_REFILL,
    PLAYER_REMOVE_HEALTH,
    PLAYER_COMMAND,
    EVENT_TYPE_COUNT
} game_event_type_t;

#endif
