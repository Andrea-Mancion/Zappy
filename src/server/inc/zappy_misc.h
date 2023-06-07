/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - miscellaneous namespace, like std in C++
*/

#ifndef ZAPPY_MISC_H_

    #define ZAPPY_MISC_H_

// Includes
    #include <stdarg.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <errno.h>
    #include <time.h>

// Attributes
    #define ATTR_UNUSED __attribute__((unused))
    #define ATTR_CLEANUP(callback) __attribute__((cleanup(callback)))
    #define ATTR_CONSTRUCTOR __attribute__((constructor))
    #define ATTR_DESTRUCTOR __attribute__((destructor))
// Error codes
    #define SUCCESS 0
    #define ERR_ALLOC 1
    #define ERR_ARGS 2
    #define ERR_SOCKET 3
    #define ERR_BIND 4
    #define ERR_COMMAND 5
    #define ERR_NETWORK 6
    #define NB_ERR 7

// Error messages
    #define ERROR_TABLE ((const char*[]) { \
        "Success", \
        "Memory allocation failed", \
        "Bad arguments were given", \
        "Invalid socket", \
        "Couldn't bind given port", \
        "Invalid command", \
        "Network error occured", \
    })

// Error handling functions
    #define ERROR(c) (c >= SUCCESS && c < NB_ERR ? ERROR_TABLE[c] : \
"Invalid error code")
    #define GET_ERRNO() (errno ? strerror(errno) : "No internal error")
    #define HANDLE_ERROR(s, m) (s ? fprintf(stderr, \
"\033[31m%s: %s - %s\n\033[0m", m, ERROR(s), GET_ERRNO()) && false : true)

#endif
