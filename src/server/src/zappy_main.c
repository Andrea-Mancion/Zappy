/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - main
*/

#include "zappy_misc.h"
#include "zappy_program.h"
#include "game/server_class.h"

const char *error_params = "Params init failed";
const char *error_server = "Server init failed";
const char *error_loop = "Server loop interrupted";
const char *invalid_parameters = "Invalid parameters. Run with -help for more "
    "info.";

// Pre-main function
ATTR_CONSTRUCTOR void premain(void)
{
    srand(time(NULL));
}

// Main function
int main(const int argc, const char *argv[])
{
    ATTR_CLEANUP(params_destroy) program_params_t params = default_params;
    ATTR_CLEANUP(server_destroy) game_server_t server = default_server;

    if (!handle_error(params_init(&params, argc - 1, argv + 1), error_params))
        return PROGRAM_EXIT_FAILURE;
    if (params.mode == HELP) {
        fprintf(stdout, "%s\n", USAGE);
        return PROGRAM_EXIT_SUCCESS;
    }
    if (!params.is_valid(&params)) {
        fprintf(stderr, "%s\n", invalid_parameters);
        return PROGRAM_EXIT_FAILURE;
    }
    if (!handle_error(server_init(&server, &params), error_server))
        return PROGRAM_EXIT_FAILURE;
    fprintf(stdout, "Port: %d\n", params.port);
    if (!handle_error(server.run(&server), error_loop))
        return PROGRAM_EXIT_FAILURE;
    return PROGRAM_EXIT_SUCCESS;
}
