/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - notifications table
*/

#include "zappy_misc.h"
#include "game/notification_class.h"
#include "game/command_class.h"

// Default graphic notification params
const graphic_notification_params_t default_graphic_notification_params = {
    .id = 0,
    .x = 0,
    .y = 0,
    .egg_id = 0,
    .resource = RESOURCE_COUNT,
    .message = NULL,
    .success = false,
    .level = 0,
    .team_name = NULL,
    .direction = 1,
};

// Table containing all of the GRAPHIC notifs and their respective functions
const graphic_notification_t graphic_notifications_table[] = {
    {"msz", &graphic_notification_msz},
    {"mct", &graphic_notification_mct},
    {"bct", &graphic_notification_bct},
    {"sgt", &graphic_notification_sgt},
    {"tna", &graphic_notification_tna},
    {"ppo", &graphic_notification_ppo},
    {"plv", &graphic_notification_plv},
    {"pin", &graphic_notification_pin},
    {"pdi", &graphic_notification_pdi},
    {"pnw", &graphic_notification_pnw},
    {"pdr", &graphic_notification_pdr},
    {"pgt", &graphic_notification_pgt},
    //{"pex", &graphic_notification_pex},
    //{"pbc", &graphic_notification_pbc},
    //{"pic", &graphic_notification_pic},
    //{"pie", &graphic_notification_pie},
    //{"pfk", &graphic_notification_pfk},
    //{"enw", &graphic_notification_enw},
    //{"eht", &graphic_notification_eht},
    //{"ebo", &graphic_notification_ebo},
    //{"edi", &graphic_notification_edi},
    //{"seg", &graphic_notification_seg},
    //{"smg", &graphic_notification_smg},
    {"suc", &graphic_notification_suc},
    {"sbp", &graphic_notification_sbp},
    {NULL, NULL}
};
