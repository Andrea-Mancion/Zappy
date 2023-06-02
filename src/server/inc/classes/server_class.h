/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - server class
*/

#ifndef SERVER_CLASS_H

    #define SERVER_CLASS_H

    #include <arpa/inet.h>
    #include <sys/select.h>

    #include "zappy_server.h"
    #include "classes/params_class.h"
    #include "classes/list_class.h"
    #include "classes/client_class.h"

// Forward declarations
typedef struct server_s server_t;

// Pair structure of the command table
typedef struct command_pair_s {
    char *command;
    int (*function)(server_t *server, client_t *client, char **args);
} command_pair_t;

// Server class
typedef struct server_s {
    int socket;
    struct sockaddr_in address;
    struct timeval timeout;
    list_t client_list;
    const command_pair_t *command_table;
    bool (*read_from_client)(struct server_s *server, client_t *client);
    bool (*run)(struct server_s *server);
    void (*destroy)(struct server_s *server);
} server_t;

// Command table defined in a separate file
extern const command_pair_t command_table[];

// Server ctor, dtor and methods
int server_init(server_t *server, params_t *params);
bool server_run(server_t *server);
bool server_read_from_client(server_t *server, client_t *client);
void server_destroy(server_t *server);

#endif
