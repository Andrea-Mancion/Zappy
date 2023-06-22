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
    int *id = malloc(sizeof(int));
    event_params_t e_params = {tick(), FOOD_TIME * 1e6, PLAYER_REMOVE_HEALTH,
        client};
    graphic_notification_params_t params = default_graphic_notification_params;

    client_init_as_ai(client, &server->map);
    *id = client->id;
    team->add(team, id);
    client->team_name = strdup(command);
    server->add_event(server, &e_params);
    dprintf(client->socket, "%d\n%d %d\n", server->max_team_capacity - team->
        size, server->map.width, server->map.height);
    params = (graphic_notification_params_t){.id = client->id, .x = client->x,
        .y = client->y, .direction = client->direction + 1, .level =
        client->level, .team_name = client->team_name
    };
    server->notify_all_graphic(server, "pnw", &params);
}

// Initialize the client as a graphic
static void init_as_graphic(game_server_t *server, game_client_t *client)
{
    graphic_notification_params_t params = default_graphic_notification_params;
    game_client_t *target;

    client->team_name = strdup("GRAPHIC");
    graphic_notification_msz(server, client, &params);
    graphic_notification_sgt(server, client, &params);
    graphic_notification_mct(server, client, &params);
    graphic_notification_tna(server, client, &params);
    for (int i = 0; i < server->clients.size; i++) {
        target = server->clients.get(&server->clients, i);
        if (target->team_name && strcmp(target->team_name, "GRAPHIC") != 0) {
            params = (graphic_notification_params_t){.id = target->id, .x =
                target->x, .y = target->y, .direction = target->direction + 1,
                .level = target->level, .team_name = target->team_name
            };
            graphic_notification_pnw(server, client, &params);
        }
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
