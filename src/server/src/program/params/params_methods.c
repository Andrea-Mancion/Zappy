/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - params class
*/

#include "zappy_program.h"

// Returns true if the params are valid, false otherwise
bool params_is_valid(program_params_t *params)
{
    if (params->port <= 0 || params->port > 40000)
        return false;
    if (params->width <= 0 || params->width > 30)
        return false;
    if (params->height <= 0 || params->height > 30)
        return false;
    if (params->max_clients <= 0 || params->max_clients > 1000)
        return false;
    if (!params->team_names || !params->team_names[0])
        return false;
    if (params->frequency <= 0 || params->frequency > 10000)
        return false;
    return true;
}
