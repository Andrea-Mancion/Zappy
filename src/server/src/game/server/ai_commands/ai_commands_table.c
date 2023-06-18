/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - commands table
*/

#include "zappy_misc.h"
#include "game/command_class.h"

// Table containing all of the AI commands and their respective functions
const game_command_t ai_commands_table[] = {
    {"Forward", &ai_command_forward, 7},
    {"Right", &ai_command_right, 7},
    {"Left", &ai_command_left, 7},
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
    {NULL, NULL, 0}
};
