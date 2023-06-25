/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - broadcast command
*/

#include "zappy_misc.h"
#include "game/server_class.h"
#include "game/client_class.h"
#include "game/notification_class.h"
#include "zappy_game.h"

char *concat_message(char **args)
{
    char *message = NULL;

    for (int i = 0; args[i]; i++) {
        if (!message)
            message = strdup(args[i]);
        else {
            message = realloc(message, strlen(message) + strlen(args[i]) + 2);
            strcat(message, " ");
            strcat(message, args[i]);
        }
    }
    return message;
}

// Broadcast command
int ai_command_broadcast(ATTR_UNUSED game_t *game, game_client_t *client,
    char **args, pending_command_t *command)
{
    char *message = concat_message(args);
    graphic_notification_pair_t *pair = malloc(sizeof(
        graphic_notification_pair_t));

    if (!pair)
        return ERR_ALLOC;
    if (!message) {
        free(pair);
        return ERR_COMMAND;
    }
    pair->params = default_graphic_notification_params;
    pair->params = (graphic_notification_params_t){.id = client->id,
        .message = strdup(message)
    };
    strcpy(pair->command, "pbc");
    command->output = strdup("ok");
    command->broadcast = strdup(message);
    free(message);
    command->graphic_notifications.add(&command->graphic_notifications, pair);
    return SUCCESS;
}
