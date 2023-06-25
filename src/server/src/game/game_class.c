/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - game class
*/

#include "misc/list_class.h"
#include "game/client_class.h"
#include "game/server_class.h"
#include "zappy_game.h"

// Initial structure of game
const game_t default_game = {
    .server = {0},
    .teams = {0},
    .map = {0},
    .events = {0},
    .frequency = 100,
    .max_team_capacity = 0,
    .destroy = &game_destroy,
    .run = &game_run,
    .add_client = &game_add_client,
    .remove_client = &game_remove_client,
    .add_event = &game_add_event,
    .remove_events = &game_remove_events,
    .set_timeout = &game_set_timeout,
    .get_timeout = &game_get_timeout,
    .get_player = &game_get_player,
    .notify_all_graphic = &game_notify_all_graphic,
    .get_direction_from_broadcast = &game_get_direction_from_broadcast
};

// Initialize the teams of the game
static int teams_init(game_t *game, program_params_t *params)
{
    list_t *team;
    char *team_name;

    map_init(&game->teams, NULL, (void (*)(void *))&list_destroy, (int (*)
    (void *, void *))&strcmp);
    for (int i = 0; params->team_names[i]; i++) {
        if (!(team = malloc(sizeof(list_t))))
            continue;
        list_init(team, NULL, client_cmp_id);
        if (!(team_name = strdup(params->team_names[i]))
            || !game->teams.set(&game->teams, team_name, team)) {
            team->destroy(team);
            free(team);
        }
    }
    return SUCCESS;
}

// Game constructor
int game_init(game_t *game, program_params_t *params)
{
    int status;

    *game = default_game;
    game->frequency = params->frequency;
    game->max_team_capacity = params->max_clients;
    list_init(&game->events, NULL, NULL);
    if ((status = server_init(&game->server, params->port))) {
        server_destroy(&game->server);
        return status;
    }
    game->server.game = game;
    if ((status = game_map_init(&game->map, params->width, params->height))) {
        game_map_destroy(&game->map);
        return status;
    }
    teams_init(game, params);
    return SUCCESS;
}

// Game destructor
void game_destroy(game_t *game)
{
    if (game->teams.destroy)
        game->teams.destroy(&game->teams);
    if (game->map.destroy)
        game->map.destroy(&game->map);
    if (game->events.destroy)
        game->events.destroy(&game->events);
    if (game->server.destroy)
        game->server.destroy(&game->server);
}
