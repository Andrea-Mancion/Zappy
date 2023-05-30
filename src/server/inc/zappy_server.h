/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - main
*/

#ifndef ZAPPY_SERVER_H

    #define ZAPPY_SERVER_H

    #include <errno.h>
    #include <stdarg.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define PROGRAM_EXIT_SUCCESS 0
    #define PROGRAM_EXIT_FAILURE 84
    #define MAX_CLIENTS 10
    #define BUF_SIZE 1024
    #define MAX_CLIENT_COMMANDS 10

    #define UNUSED __attribute__((unused))
    #define CLEANUP(callback) __attribute__((cleanup(callback)))

    #define USAGE \
        "USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ..." \
        " -c clientsNb -f freq\n" \
        "\tport\t\tis the port number\n" \
        "\twidth\t\tis the width of the world\n" \
        "\theight\t\tis the height of the world\n" \
        "\tnameX\t\tis the name of the team X\n" \
        "\tclientsNb\tis the number of authorized clients per team\n" \
        "\tfreq\t\tis the reciprocal of time unit for execution of actions\n"

    #define SUCCESS 0
    #define ERR_ALLOC 1
    #define ERR_ARGS 2
    #define ERR_SOCKET 3
    #define ERR_BIND 4
    #define ERR_COMMAND 5
    #define NB_ERR 6

    #define ERROR_TABLE ((const char*[]) { \
        "Success", \
        "Memory allocation failed", \
        "Bad arguments were given", \
        "Invalid socket", \
        "Couldn't bind given port", \
        "Invalid command transmitted", \
    })

    #define ERROR(c) (c >= SUCCESS && c < NB_ERR ? ERROR_TABLE[c] : \
"Invalid error code")
    #define GET_ERRNO() (errno ? strerror(errno) : "No internal error")

#endif
