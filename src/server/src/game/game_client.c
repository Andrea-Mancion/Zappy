/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - game class
*/

#include "zappy_misc.h"
#include "game/command_class.h"
#include "game/notification_class.h"
#include "game/event_class.h"

// Initializes a client as a player
static bool init_client(game_client_t *client, game_map_t *map, int *id2)
{
    static int id = 0;
    int *player_id;

    client->direction = rand() % DIRECTION_COUNT;
    client->x = rand() % map->width;
    client->y = rand() % map->height;
    client->id = ++id;
    if (!(player_id = malloc(sizeof(int))))
        return false;
    *player_id = client->id;
    *id2 = client->id;
    map->tiles[client->y][client->x].players.add(&map->tiles[client->y]
        [client->x].players, player_id);
    return true;
}

// Initialize the client as an AI
static int init_as_ai(game_t *game, game_client_t *client,
    char *team_name)
{
    int *id = malloc(sizeof(int));
    list_t *team;
    event_params_t e = {tick(), FOOD_TIME * 1e6, PLAYER_REMOVE_HEALTH, client};
    graphic_notification_params_t params = default_graphic_notification_params;
    if (!id || !init_client(client, &game->map, id))
        return ERR_ALLOC;
    if (!(team = game->teams.get(&game->teams, team_name)))
        return ERR_COMMAND;
    if (!(client->team_name = strdup(team_name)))
        return ERR_ALLOC;
    team->add(team, id);
    game->add_event(game, &e);
    dprintf(client->socket, "%d\n%d %d\n", game->max_team_capacity - team->
        size, game->map.width, game->map.height);
    params = (graphic_notification_params_t){.id = client->id, .x = client->x,
        .y = client->y, .direction = client->direction + 1, .level =
        client->level, .team_name = client->team_name
    };
    game->notify_all_graphic(game, "pnw", &params);
    return SUCCESS;
}

// Initialize the client as a graphic
static int init_as_graphic(game_t *game, game_client_t *client)
{
    graphic_notification_params_t params = default_graphic_notification_params;
    game_client_t *target;

    if (!(client->team_name = strdup("GRAPHIC")))
        return ERR_ALLOC;
    graphic_notification_msz(game, client, &params);
    graphic_notification_sgt(game, client, &params);
    graphic_notification_mct(game, client, &params);
    graphic_notification_tna(game, client, &params);
    for (int i = 0; i < game->server.clients.size; i++) {
        target = game->server.clients.get(&game->server.clients, i);
        if (target->team_name && strcmp(target->team_name, "GRAPHIC") != 0) {
            params = (graphic_notification_params_t){.id = target->id, .x =
                target->x, .y = target->y, .direction = target->direction + 1,
                .level = target->level, .team_name = target->team_name
            };
            graphic_notification_pnw(game, client, &params);
        }
    }
    return SUCCESS;
}

// Give a team name to the client
int game_add_client(game_t *game, game_client_t *client,
    char *team_name)
{
    int status;

    if (strcmp(team_name, "GRAPHIC") == 0)
        status = init_as_graphic(game, client);
    else
        status = init_as_ai(game, client, team_name);
    if (status != SUCCESS)
        dprintf(client->socket, "ko\n");
    return status;
}

// Give a team name to the client
void game_remove_client(game_t *game, game_client_t *client)
{
    list_t *team;
    graphic_notification_params_t params = {.id = client->id};
    int index;

    if (client->team_name && strcmp(client->team_name, "GRAPHIC") == 0) {
        free(client->team_name);
        client->team_name = NULL;
        return;
    }
    game->notify_all_graphic(game, "pdi", &params);
    if ((team = game->teams.get(&game->teams, client->team_name)))
        if ((index = team->index(team, &client->id)) < team->size)
            team->remove(team, index);
    team = &game->map.tiles[client->y][client->x].players;
    if ((index = team->index(team, &client->id)) < team->size)
        team->remove(team, index);
    game->remove_events(game, PLAYER_COMMAND, client);
    game->remove_events(game, PLAYER_REMOVE_HEALTH, client);
    free(client->team_name);
    client->team_name = NULL;
}
