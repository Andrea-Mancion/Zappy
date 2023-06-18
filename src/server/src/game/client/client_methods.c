/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - client class
*/

#include "zappy_game.h"
#include "game/client_class.h"

// Compare function for clients
int client_cmp(void *a, void *b)
{
    game_client_t *client_a = a;
    game_client_t *client_b = b;

    return client_a - client_b;
}
