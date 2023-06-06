/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - game namespace
*/

#ifndef ZAPPY_GAME_H

    #define ZAPPY_GAME_H

    #include <arpa/inet.h>
    #include <sys/select.h>

// Settings
    #define MAX_CLIENTS 10
    #define BUF_SIZE 1024
    #define MAX_CLIENT_COMMANDS 10
    #define REFILL_TIME 20
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

#endif
