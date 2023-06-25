/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - object commands
*/

#include "zappy_misc.h"
#include "game/server_class.h"
#include "game/client_class.h"
#include "game/notification_class.h"
#include "zappy_game.h"

const char *resource_names[] = {
    [FOOD] = "food",
    [LINEMATE] = "linemate",
    [DERAUMERE] = "deraumere",
    [SIBUR] = "sibur",
    [MENDIANE] = "mendiane",
    [PHIRAS] = "phiras",
    [THYSTAME] = "thystame",
};

const double resource_quantities[] = {
    [FOOD] = .5,
    [LINEMATE] = .3,
    [DERAUMERE] = .15,
    [SIBUR] = .1,
    [MENDIANE] = .1,
    [PHIRAS] = .08,
    [THYSTAME] = .05,
};

static void graphic_notification_pair_init(graphic_notification_pair_t *
    pair, game_client_t *client, char *command, game_resource_t resource)
{
    pair->params = default_graphic_notification_params;
    pair->params = (graphic_notification_params_t){.id = client->id,
        .resource = resource
    };
    strcpy(pair->command, command);
}

static int check_status(graphic_notification_pair_t *pair, char *arg,
    game_resource_t *enum_resource)
{
    if (!pair)
        return ERR_ALLOC;
    if (arg == NULL) {
        free(pair);
        return ERR_COMMAND;
    }
    for (int i = 0; i < RESOURCE_COUNT; i++)
        if (strcmp(arg, resource_names[i]) == 0)
            *enum_resource = i;
    if (*enum_resource == RESOURCE_COUNT) {
        free(pair);
        return ERR_COMMAND;
    }
    return SUCCESS;
}

// Get resource address from tile
static int *get_resource_address(game_t *game, game_client_t *client,
    game_resource_t resource)
{
    game_tile_t *tile = &game->map.tiles[client->y][client->x];
    int *resources_addresses[] = {[FOOD] = &tile->food, [LINEMATE] =
        &tile->linemate, [DERAUMERE] = &tile->deraumere, [SIBUR] =
        &tile->sibur, [MENDIANE] = &tile->mendiane, [PHIRAS] = &tile->phiras,
        [THYSTAME] = &tile->thystame};

    return resources_addresses[resource];
}

// Take command
int ai_command_take(game_t *game, game_client_t *client,
    char **args, pending_command_t *command)
{
    game_resource_t enum_resource = RESOURCE_COUNT;
    graphic_notification_pair_t *pair = malloc(sizeof(
        graphic_notification_pair_t));
    int *address;
    int status;

    if ((status = check_status(pair, args[0], &enum_resource)) != SUCCESS)
        return status;
    if (!*(address = get_resource_address(game, client, enum_resource))) {
        command->output = strdup("ko");
        free(pair);
        return SUCCESS;
    }
    graphic_notification_pair_init(pair, client, "pgt", enum_resource);
    *address -= 1;
    *game->map.get_resource_address(&game->map, enum_resource) -= 1;
    client->inventory[enum_resource] += 1;
    command->output = strdup("ok");
    command->graphic_notifications.add(&command->graphic_notifications, pair);
    return SUCCESS;
}

// Set command
int ai_command_set(game_t *game, game_client_t *client,
    char **args, pending_command_t *command)
{
    game_resource_t enum_resource = RESOURCE_COUNT;
    graphic_notification_pair_t *pair = malloc(sizeof(
        graphic_notification_pair_t));
    int status;

    if ((status = check_status(pair, args[0], &enum_resource)) != SUCCESS)
        return status;
    if (client->inventory[enum_resource] == 0) {
        command->output = strdup("ko");
        free(pair);
        return SUCCESS;
    }
    graphic_notification_pair_init(pair, client, "pdr", enum_resource);
    *get_resource_address(game, client, enum_resource) += 1;
    *game->map.get_resource_address(&game->map, enum_resource) += 1;
    client->inventory[enum_resource] -= 1;
    command->output = strdup("ok");
    command->graphic_notifications.add(&command->graphic_notifications, pair);
    return SUCCESS;
}
