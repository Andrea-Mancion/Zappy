/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - game namespace
*/

#ifndef ZAPPY_GAME_H_

    #define ZAPPY_GAME_H_

    #include <arpa/inet.h>
    #include <sys/select.h>
    #include <stddef.h>

// Settings
    #define MAX_CLIENTS 100
    #define BUF_SIZE 1024
    #define MAX_PENDING_COMMANDS 10
    #define REFILL_TIME 20
    #define FOOD_TIME 126
    #define MAX_LEVEL 8
// Resource densities
    #define FOOD_DENSITY 0.5
    #define LINEMATE_DENSITY 0.3
    #define DERAUMERE_DENSITY 0.15
    #define SIBUR_DENSITY 0.1
    #define MENDIANE_DENSITY 0.1
    #define PHIRAS_DENSITY 0.08
    #define THYSTAME_DENSITY 0.05

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

typedef struct game_resource_name_pair_s {
    char *name;
    game_resource_t resource;
} game_resource_name_pair_t;

// Resources names array
extern const game_resource_name_pair_t resource_names[];

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
