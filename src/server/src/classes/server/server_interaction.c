/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - server class
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zappy_server.h"
#include "classes/server_class.h"

bool server_read_from_client(server_t *server, int client_fd)
{
    char buffer[BUF_SIZE];

    (void)server;
    memset(buffer, '\0', BUF_SIZE);
    if (read(client_fd, buffer, BUF_SIZE) <= 0) {
        close(client_fd);
        return false;
    }
    // TODO: push buffer dans le circular_buffer du client, traiter la commande
    // oui parce que buffer management
    return true;
}
