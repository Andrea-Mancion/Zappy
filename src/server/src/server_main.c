/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - main
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "zappy_server.h"
#include "classes/params_class.h"
#include "classes/server_class.h"

static const char *usage = ""
    "USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ... -c cl"
    "ientsNb -f freq\n"
    "\tport\t\tis the port number\n"
    "\twidth\t\tis the width of the world\n"
    "\theight\t\tis the height of the world\n"
    "\tnameX\t\tis the name of the team X\n"
    "\tclientsNb\tis the number of authorized clients per team\n"
    "\tfreq\t\tis the reciprocal of time unit for execution of actions\n";

int breakout(int status, params_t *params, server_t *server)
{
    if (server)
        server->destroy(server);
    if (params)
        params->destroy(params);
    return status;
}

int main(const int argc, const char *argv[])
{
    params_t params;
    server_t server;

    params_init(&params, argc - 1, argv + 1);
    if (params.mode == HELP) {
        printf("%s", usage);
        return breakout(0, &params, NULL);
    } else if (!params.is_valid(&params)) {
        printf("Invalid parameters.\n%s", usage);
        return breakout(84, &params, NULL);
    }
    server_init(&server, &params);
    if (server.socket == -1) {
        printf("Socket creation failed. Port may already be in use.\n");
        return breakout(84, &params, &server);
    }
    while (server.run(&server));
    return breakout(0, &params, &server);
}
