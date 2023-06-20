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
    game_client_t *target;
    int *id = malloc(sizeof(int));
    event_params_t params = {tick(), FOOD_TIME * 1e6, PLAYER_REMOVE_HEALTH,
        client};
    client_init_as_ai(client, &server->map);
    *id = client->id;
    team->add(team, id);
    client->team_name = strdup(command);
    server->add_event(server, &params);
    dprintf(client->socket, "%d\n%d %d\n", server->max_team_capacity - team->
        size, server->map.width, server->map.height);
    for (int i = 0; i < server->clients.size; i++) {
        target = server->clients.get(&server->clients, i);
        if (target->team_name && strcmp(target->team_name, "GRAPHIC") == 0) {
            dprintf(target->socket, "pnw %d %d %d %d %d %s\n", client->id,
                client->x, client->y, client->direction + 1,
                client->level, client->team_name);
            graphic_command_mct(server, target, (char *[]){NULL});
        }
    }
}

static void init_as_graphic(game_server_t *server, game_client_t *client)
{
    game_client_t *target;

    client->team_name = strdup("GRAPHIC");
    graphic_command_msz(server, client, (char *[]){NULL});
    graphic_command_sgt(server, client, (char *[]){NULL});
    graphic_command_mct(server, client, (char *[]){NULL});
    graphic_command_tna(server, client, (char *[]){NULL});
    for (int i = 0; i < server->clients.size; i++) {
        target = server->clients.get(&server->clients, i);
        if (target->team_name && strcmp(target->team_name, "GRAPHIC") != 0)
            dprintf(client->socket, "pnw %d %d %d %d %d %s\n", target->id,
                target->x, target->y, target->direction + 1,
                target->level, target->team_name);
    }
}

// Give a team name to the client
int server_init_client(game_server_t *server, game_client_t *client,
    char *team_name)
{
    list_t *team = server->teams.get(&server->teams, team_name);

    if (strcmp(team_name, "GRAPHIC") == 0) {
        init_as_graphic(server, client);
        return SUCCESS;
    }
    if (!team) {
        dprintf(client->socket, "ko\n");
        return ERR_COMMAND;
    }
    init_as_ai(server, team, client, team_name);
    return SUCCESS;
}
