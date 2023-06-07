/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - commands table
*/

#include "zappy_misc.h"
#include "game/commands_list.h"

// Table containing all of the commands and their respective functions
const command_pair_t command_table[] = {
    {"Forward", &command_forward},
    {"Right", &command_right},
    {"Left", &command_left},
    /*
    {"Look", &command_look},
    {"Inventory", &command_inventory},
    {"Broadcast", &command_broadcast},
    {"Connect_nbr", &command_connect_nbr},
    {"Fork", &command_fork},
    {"Eject", &command_eject},
    {"Take", &command_take},
    {"Set", &command_set},
    {"Incantation", &command_incantation},
    */
    {NULL, NULL}
};
