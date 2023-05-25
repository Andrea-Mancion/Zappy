/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - params class
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "classes/params_class.h"

static const params_t default_params = {
    .mode = RUN,
    .port = 0,
    .width = 0,
    .height = 0,
    .team_names = NULL,
    .max_clients = 0,
    .is_valid = &params_is_valid,
    .destroy = &params_destroy,
};

static char **get_variadic_args(const int argc, const char *argv[])
{
    char **args;
    int i;

    for (i = 0; i < argc && argv[i][0] != '-'; i++);
    args = malloc(sizeof(char *) * (i + 1));
    args[i] = NULL;
    for (i -= 1; i >= 0; i--)
        args[i] = strdup(argv[i]);
    return args;
}

void params_init(params_t *params, const int argc, const char *argv[])
{
    *params = default_params;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0)
            params->port = atoi(argv[++i]);
        if (strcmp(argv[i], "-x") == 0)
            params->width = atoi(argv[++i]);
        if (strcmp(argv[i], "-y") == 0)
            params->height = atoi(argv[++i]);
        if (strcmp(argv[i], "-c") == 0)
            params->max_clients = atoi(argv[++i]);
        if (strcmp(argv[i], "-help") == 0)
            params->mode = HELP;
        if (strcmp(argv[i], "-n") == 0)
            params->team_names = get_variadic_args(argc - i, argv + i);
    }
}

bool params_is_valid(params_t *params)
{
    if (params->port <= 0 || params->port > 40000)
        return false;
    if (params->width <= 0 || params->width > 1000)
        return false;
    if (params->height <= 0 || params->height > 1000)
        return false;
    if (params->max_clients <= 0 || params->max_clients > 1000)
        return false;
    return true;
}

void params_destroy(params_t *params)
{
    if (!params->team_names)
        return;
    for (int i = 0; params->team_names[i]; i++)
        free(params->team_names[i]);
    free(params->team_names);
}
