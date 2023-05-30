/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - main
*/

#include "zappy_server.h"
#include "classes/params_class.h"
#include "classes/server_class.h"

const char *error_params = "Params init failed";
const char *error_server = "Server init failed";
const char *invalid_parameters = "Invalid parameters. Run with -help for more "
    "info.";

// Main function
int main(const int argc, const char *argv[])
{
    CLEANUP(params_destroy) params_t params;
    CLEANUP(server_destroy) server_t server;

    if (!HANDLE_ERROR(params_init(&params, argc - 1, argv + 1), error_params))
        return PROGRAM_EXIT_FAILURE;
    if (!params.is_valid(&params)) {
        fprintf(stderr, "%s\n", invalid_parameters);
        return PROGRAM_EXIT_FAILURE;
    }
    if (params.mode == HELP) {
        fprintf(stdout, "%s\n", USAGE);
        return PROGRAM_EXIT_SUCCESS;
    }
    if (!HANDLE_ERROR(server_init(&server, &params), error_server))
        return PROGRAM_EXIT_FAILURE;
    while (server.run(&server));
    return PROGRAM_EXIT_SUCCESS;
}
