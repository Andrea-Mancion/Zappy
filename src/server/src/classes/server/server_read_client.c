/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - server class
*/

#include <unistd.h>
#include "zappy_server.h"
#include "classes/server_class.h"

static const char *error_command = "Couldn't execute command";

// Finds the command in the table and executes it, returns false if not found
static int server_execute_command(server_t *server, client_t *client,
    char *command, char **args)
{
    for (int i = 0; server->command_table[i].command; i++) {
        if (strcmp(server->command_table[i].command, command) == 0)
            return server->command_table[i].function(server, client, args);
    }
    return ERR_COMMAND;
}

// Parses a client-given command and executes it
static int server_parse_command(server_t *server, client_t *client,
    char *command)
{
    char **args = malloc(sizeof(char *) * (strlen(command) + 1));
    int j = 0;
    int status = ERR_COMMAND;

    if (!args)
        return ERR_ALLOC;
    for (char *sub = strtok(command, " "); sub; sub = strtok(NULL, " "))
        args[j++] = sub;
    args[j] = NULL;
    if (!args[0] || (status = server_execute_command(
        server, client, *args, args + 1) != SUCCESS)) {
        free(args);
        return status;
    }
    free(args);
    return SUCCESS;
}

// Parses the buffer of the client
static void server_parse_client(server_t *server, client_t *client)
{
    char *token = strtok(client->buffer, "\n");
    char *next_token;

    for (int i = 0; i < MAX_CLIENT_COMMANDS && token; i++) {
        next_token = strtok(token + strlen(token) + 1, "\n");
        HANDLE_ERROR(server_parse_command(server, client, token),
            error_command);
        token = next_token;
    }
}

// Reads from the client, returns false if the client disconnected
bool server_read_from_client(server_t *server, client_t *client)
{
    char buffer[BUF_SIZE];
    int readlen = read(client->socket, buffer, BUF_SIZE);
    int buflen = strlen(client->buffer);

    if (readlen <= 0) {
        close(client->socket);
        return false;
    }
    buffer[readlen] = '\0';
    strncat(client->buffer, buffer, BUF_SIZE - buflen - 1);
    if (buffer[readlen - 1] != '\n')
        return true;
    server_parse_client(server, client);
    client->buffer[0] = '\0';
    return true;
}
