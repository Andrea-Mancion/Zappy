/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - params class
*/

#include "zappy_misc.h"
#include "zappy_program.h"

// Initial structure of params
const program_params_t default_params = {
    .mode = RUN,
    .port = 0,
    .width = 0,
    .height = 0,
    .team_names = NULL,
    .max_clients = 0,
    .frequency = 100,
    .is_valid = &params_is_valid,
    .destroy = &params_destroy,
};

// Returns arguments as an array of strings for multi-args options
static char **get_variadic_args(const int argc, const char *argv[])
{
    char **args;
    int i;

    for (i = 0; i < argc && argv[i][0] != '-'; i++);
    args = malloc(sizeof(char *) * (i + 1));
    if (!args)
        return NULL;
    args[i] = NULL;
    for (i -= 1; i >= 0; i--)
        args[i] = strdup(argv[i]);
    return args;
}

// Params constructor
int params_init(program_params_t *params, const int argc, const char *argv[])
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
            params->team_names = get_variadic_args(argc - i - 1, argv + i + 1);
        if (strcmp(argv[i], "-f") == 0)
            params->frequency = atoi(argv[++i]);
    }
    return SUCCESS;
}

// Params destructor
void params_destroy(program_params_t *params)
{
    if (!params->team_names)
        return;
    for (int i = 0; params->team_names[i]; i++)
        free(params->team_names[i]);
    free(params->team_names);
}
