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
#include "game/map_class.h"
#include "zappy_game.h"

// Initial structure of client
static const game_client_t default_client = {
    .socket = -1,
    .team_name = NULL,
    .buffer = NULL,
    .player_num = -1,
    .direction = EAST,
    .x = 0,
    .y = 0,
    .destroy = &client_destroy,
};

// Client constructor
int client_init(game_client_t *client, int socket, game_map_t *map)
{
    static int player_num = 0;

    if (socket < 0)
        return ERR_SOCKET;
    *client = default_client;
    client->socket = socket;
    client->direction = rand() % 4;
    client->x = rand() % map->width;
    client->y = rand() % map->height;
    client->player_num = ++player_num;
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
