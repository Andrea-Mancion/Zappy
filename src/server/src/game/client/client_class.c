/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - client class
*/

#include <unistd.h>
#include "zappy_misc.h"
#include "zappy_game.h"
#include "game/client_class.h"

// Initial structure of client
static const game_client_t default_client = {
    .socket = -1,
    .team_name = NULL,
    .buffer = NULL,
    .destroy = &client_destroy,
};

// Client constructor
int client_init(game_client_t *client, int socket)
{
    if (socket < 0)
        return ERR_SOCKET;
    *client = default_client;
    client->socket = socket;
    if (!(client->buffer = malloc(sizeof(char) * BUF_SIZE)))
        return ERR_ALLOC;
    memset(client->buffer, '\0', BUF_SIZE);
    return SUCCESS;
}

// Client destructor
void client_destroy(game_client_t *client)
{
    if (client->socket >= 0)
        close(client->socket);
    if (client->team_name)
        free(client->team_name);
    if (client->buffer)
        free(client->buffer);
}
