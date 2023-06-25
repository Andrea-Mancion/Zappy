/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - program namespace
*/

#ifndef ZAPPY_PROGRAM_H_

    #define ZAPPY_PROGRAM_H_

    #include "zappy_misc.h"

// Exit codes
    #define PROGRAM_EXIT_SUCCESS 0
    #define PROGRAM_EXIT_FAILURE 84

// Program usage
extern const char *program_usage;

// Enum for the different modes for the program to run in
typedef enum program_mode_e {
    HELP,
    RUN,
} program_mode_t;

// Params class
typedef struct program_params_s {
    program_mode_t mode;
    int port;
    int width;
    int height;
    char **team_names;
    int max_clients;
    int frequency;
    bool (*is_valid)(struct program_params_s *params);
    void (*destroy)(struct program_params_s *params);
} program_params_t;

// Initial structure of params
extern const program_params_t default_params;

// Params ctor, dtor and methods
int params_init(program_params_t *params, const int argc, const char *argv[]);
bool params_is_valid(program_params_t *params);
void params_destroy(program_params_t *params);

#endif
