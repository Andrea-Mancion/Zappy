/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - commands table
*/

#include "zappy_misc.h"
#include "game/commands_list.h"

// Table containing all of the commands and their respective functions
const game_command_t command_table[] = {
    {"Forward", &command_forward, 7},
    {"Right", &command_right, 7},
    {"Left", &command_left, 7},
    /*
    {"Look", &command_look, 7},
    {"Inventory", &command_inventory, 1},
    {"Broadcast", &command_broadcast, 7},
    {"Connect_nbr", &command_connect_nbr, 0},
    {"Fork", &command_fork, 42},
    {"Eject", &command_eject, 7},
    {"Take", &command_take, 7},
    {"Set", &command_set, 7},
    {"Incantation", &command_incantation, 300},
    */
    {NULL, NULL}
};
