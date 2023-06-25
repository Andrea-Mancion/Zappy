/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - events table
*/

#include "zappy_misc.h"
#include "game/event_class.h"
#include "zappy_game.h"

// Table containing all of the events and their respective functions
void (*events_table[])(game_t *, game_client_t *) = {
    [MAP_REFILL] = &event_refill,
    [PLAYER_REMOVE_HEALTH] = &event_remove_player_health,
    [PLAYER_COMMAND] = &event_end_command,
};
