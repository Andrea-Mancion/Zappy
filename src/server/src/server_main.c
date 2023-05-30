/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - main
*/

#include "zappy_server.h"
#include "classes/params_class.h"
#include "classes/server_class.h"

const char *invalid_parameters = "Invalid parameters. Run with -help for more "
    "info.\n";
const char *error_server_init = "Server_init() failed: %s - %s\n";

// Main function
int main(const int argc, const char *argv[])
{
    CLEANUP(params_destroy) params_t params;
    CLEANUP(server_destroy) server_t server;
    int server_return;

    params_init(&params, argc - 1, argv + 1);
    if (!params.is_valid(&params)) {
        fprintf(stderr, invalid_parameters);
        return PROGRAM_EXIT_FAILURE;
    }
    if (params.mode == HELP) {
        fprintf(stdout, USAGE);
        return PROGRAM_EXIT_SUCCESS;
    }
    server_return = server_init(&server, &params);
    if (server_return != 0) {
        fprintf(stderr, error_server_init, ERROR(server_return), GET_ERRNO());
        return PROGRAM_EXIT_FAILURE;
    }
    while (server.run(&server));
    return PROGRAM_EXIT_SUCCESS;
}
