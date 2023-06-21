/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - commands table
*/

#include "zappy_misc.h"
#include "game/command_class.h"

// Table containing all of the GRAPHIC commands and their respective functions
const game_graphic_command_t graphic_commands_table[] = {
    {"msz", &graphic_command_msz},
    {"bct", &graphic_command_bct},
    {"mct", &graphic_command_mct},
    {"tna", &graphic_command_tna},
    {"ppo", &graphic_command_ppo},
    {"plv", &graphic_command_plv},
    {"pin", &graphic_command_pin},
    {"sgt", &graphic_command_sgt},
    {"sst", &graphic_command_sst},
    {NULL, NULL}
};
