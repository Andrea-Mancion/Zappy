/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - params class
*/

#ifndef PARAMS_CLASS_H

    #define PARAMS_CLASS_H

    #include "zappy_server.h"

enum mode {
    HELP,
    RUN,
};

typedef struct params_s {
    enum mode mode;
    int port;
    int width;
    int height;
    char **team_names;
    int max_clients;
    bool (*is_valid)(struct params_s *params);
    void (*destroy)(struct params_s *params);
} params_t;

void params_init(params_t *params, const int argc, const char *argv[]);
bool params_is_valid(params_t *params);
void params_destroy(params_t *params);

#endif
