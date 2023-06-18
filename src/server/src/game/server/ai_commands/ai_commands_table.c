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
    {"Take", &ai_command_take, 7},
    {"Set", &ai_command_set, 7},
    /*
    {"Look", &ai_command_look, 7},
    {"Inventory", &ai_command_inventory, 1},
    {"Broadcast", &ai_command_broadcast, 7},
    {"Connect_nbr", &ai_command_connect_nbr, 0},
    {"Fork", &ai_command_fork, 42},
    {"Eject", &ai_command_eject, 7},
    {"Incantation", &ai_command_incantation, 300},
    */
    {NULL, NULL, 0}
};
