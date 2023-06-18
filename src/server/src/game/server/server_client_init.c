/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - server class
*/

#include <unistd.h>
#include "zappy_misc.h"
#include "game/command_class.h"
#include "game/event_class.h"

// Initialize the client as an AI
static void init_as_ai(game_server_t *server, list_t *team, game_client_t *
    client, char *command)
{
    game_client_t **id = malloc(sizeof(game_client_t *));
    event_params_t params = {tick(), FOOD_TIME * 1e6, PLAYER_REMOVE_HEALTH,
        client};

    client_init_as_ai(client, &server->map);
    *id = client;
    team->add(team, id);
    client->team_name = strdup(command);
    server->add_event(server, &params);
    dprintf(client->socket, "%d\n", server->max_team_capacity - team->size);
    dprintf(client->socket, "%d %d\n", server->map.width, server->map.height);
}

// Give a team name to the client
int server_init_client(game_server_t *server, game_client_t *client,
    char *team_name)
{
    list_t *team = server->teams.get(&server->teams, team_name);

    if (strcmp(team_name, "GRAPHIC") == 0) {
        client->team_name = strdup(team_name);
        return SUCCESS;
    } else if (!team) {
        dprintf(client->socket, "ko\n");
        return ERR_COMMAND;
    }
    init_as_ai(server, team, client, team_name);
    return SUCCESS;
}
