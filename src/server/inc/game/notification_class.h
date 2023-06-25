/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - game namespace
*/

#ifndef ZAPPY_GAME_NOTIFICATIONS_H_

    #define ZAPPY_GAME_NOTIFICATIONS_H_

    #include "zappy_game.h"
    #include "game/server_class.h"
    #include "game/client_class.h"

// Graphic notification params structure
typedef struct graphic_notification_params_s {
    int id;
    int x;
    int y;
    int egg_id;
    game_resource_t resource;
    char *message;
    bool success;
    game_direction_t direction;
    char *team_name;
    int level;
} graphic_notification_params_t;

// Default structure of graphic notification params
extern const graphic_notification_params_t default_graphic_notification_params;

// Graphic notifications
void graphic_notification_msz(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_bct(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_mct(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_tna(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_ppo(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_plv(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_pin(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_sgt(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_pnw(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_pex(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_pbc(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_pic(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_pie(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_pfk(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_pdr(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_pgt(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_pdi(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_enw(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_eht(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_ebo(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_edi(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_seg(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_smg(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_suc(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);
void graphic_notification_sbp(game_t *game, game_client_t *client,
    graphic_notification_params_t *params);

// Graphic notifications table

typedef struct graphic_notification_s {
    char *command;
    void (*function)(game_t *game, game_client_t *client,
        graphic_notification_params_t *params);
} graphic_notification_t;

typedef struct graphic_notification_pair_s {
    graphic_notification_params_t params;
    char command[4];
} graphic_notification_pair_t;

extern const graphic_notification_t graphic_notifications_table[];

#endif
