/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - main
*/

#include "zappy_program.h"
#include "game/server_class.h"

static const char *error_params = "Params init failed";
static const char *error_game = "Game init failed";
static const char *invalid_parameters = "Invalid parameters. Run with -help "
    "for more info.";
const char *program_usage = "USAGE: ./zappy_server -p port -x width -y height "
    "-n name1 name2 ... -c clientsNb -f freq\n\tport\tis the port number\n\t"
    "width\tis the width of the world\n\theight\tis the height of the world\n"
    "\tnameX\tis the name of the team X\n\tclientsNb\tis the number of "
    "authorized clients per team\n\tfreq\tis the reciprocal of time unit for "
    "execution of actions\n";

// Pre-main function
ATTR_CONSTRUCTOR void premain(void)
{
    srand(time(NULL));
}

// Main function
int main(const int argc, const char *argv[])
{
    ATTR_CLEANUP(params_destroy) program_params_t params = default_params;
    ATTR_CLEANUP(game_destroy) game_t game = default_game;

    if (!handle_error(params_init(&params, argc - 1, argv + 1), error_params))
        return PROGRAM_EXIT_FAILURE;
    if (params.mode == HELP) {
        fprintf(stdout, "%s\n", program_usage);
        return PROGRAM_EXIT_SUCCESS;
    }
    if (!params.is_valid(&params)) {
        fprintf(stderr, "%s\n", invalid_parameters);
        return PROGRAM_EXIT_FAILURE;
    }
    if (!handle_error(game_init(&game, &params), error_game))
        return PROGRAM_EXIT_FAILURE;
    game.run(&game);
    return PROGRAM_EXIT_SUCCESS;
}
