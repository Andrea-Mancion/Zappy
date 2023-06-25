/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - movement commands
*/

#include "zappy_misc.h"
#include "game/server_class.h"
#include "game/client_class.h"
#include "game/notification_class.h"
#include "zappy_game.h"

static const int direction_increment_forward[][2] = {
    [NORTH] = {0, -1},
    [EAST] = {1, 0},
    [SOUTH] = {0, 1},
    [WEST] = {-1, 0},
};

static void graphic_notification_pair_init(graphic_notification_pair_t *
    pair, game_client_t *client)
{
    pair->params = default_graphic_notification_params;
    pair->params = (graphic_notification_params_t){.id = client->id,
        .x = client->x, .y = client->y, .direction = client->direction
    };
    strcpy(pair->command, "ppo");
}

// Forward command
int ai_command_forward(game_t *game, game_client_t *client,
    ATTR_UNUSED char **args, pending_command_t *command)
{
    int index = game->map.tiles[client->y][client->x].players.index(
        &game->map.tiles[client->y][client->x].players, &client->id);
    int *player = malloc(sizeof(int));
    graphic_notification_pair_t *pair = malloc(sizeof(
        graphic_notification_pair_t));
    if (!player || !pair)
        return ERR_ALLOC;
    *player = client->id;
    game->map.tiles[client->y][client->x].players.remove(
        &game->map.tiles[client->y][client->x].players, index);
    client->x = (client->x + direction_increment_forward[client->direction][0]
        + game->map.width) % game->map.width;
    client->y = (client->y + direction_increment_forward[client->direction][1]
        + game->map.height) % game->map.height;
    graphic_notification_pair_init(pair, client);
    game->map.tiles[client->y][client->x].players.add(
        &game->map.tiles[client->y][client->x].players, player);
    command->output = strdup("ok");
    command->graphic_notifications.add(&command->graphic_notifications, pair);
    return SUCCESS;
}

// Right command
int ai_command_right(ATTR_UNUSED game_t *game, game_client_t *client,
    ATTR_UNUSED char **args, pending_command_t *command)
{
    graphic_notification_pair_t *pair = malloc(sizeof(
        graphic_notification_pair_t));

    if (!pair)
        return ERR_ALLOC;
    client->direction = (client->direction + 1) % DIRECTION_COUNT;
    graphic_notification_pair_init(pair, client);
    command->output = strdup("ok");
    command->graphic_notifications.add(&command->graphic_notifications, pair);
    return SUCCESS;
}

// Left command
int ai_command_left(ATTR_UNUSED game_t *game, game_client_t *client,
    ATTR_UNUSED char **args, pending_command_t *command)
{
    graphic_notification_pair_t *pair = malloc(sizeof(
        graphic_notification_pair_t));

    if (!pair)
        return ERR_ALLOC;
    client->direction = (client->direction - 1 + DIRECTION_COUNT) %
        DIRECTION_COUNT;
    graphic_notification_pair_init(pair, client);
    command->output = strdup("ok");
    command->graphic_notifications.add(&command->graphic_notifications, pair);
    return SUCCESS;
}
