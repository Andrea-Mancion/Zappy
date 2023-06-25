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
    #include <unistd.h>

// Tick function - returns current time in microseconds
    #ifndef CLOCK_REALTIME
        #define CLOCK_REALTIME 0
    #endif

static inline long long int tick(void)
{
    struct timespec ts;

    clock_gettime(CLOCK_REALTIME, &ts);
    return (ts.tv_sec * 1e6 + ts.tv_nsec / 1e3);
}

// Attributes
    #define ATTR_UNUSED __attribute__((unused))
    #define ATTR_CLEANUP(callback) __attribute__((cleanup(callback)))
    #define ATTR_CONSTRUCTOR __attribute__((constructor))
    #define ATTR_DESTRUCTOR __attribute__((destructor))
// Error codes
    #define SUCCESS 0
    #define ERR_ALLOC 1
    #define ERR_SOCKET 2
    #define ERR_BIND 3
    #define ERR_COMMAND 4
    #define ERR_NETWORK 5
    #define NB_ERR 6

// Abs function
    #define ABS(x) ((x) < 0 ? -(x) : (x))

// Error messages
    #define ERROR_TABLE ((const char*[]) { \
        "Success", \
        "Memory allocation failed", \
        "Invalid socket", \
        "Couldn't bind given port", \
        "Couldn't recognize command", \
        "Network error occured", \
        "Invalid command", \
    })

// Error handling functions
    #define ERROR(c) (c >= SUCCESS && c < NB_ERR ? ERROR_TABLE[c] : \
"Invalid error code")
    #define GET_ERRNO() (errno ? strerror(errno) : "No internal error")

// Prints error if status isn't SUCCESS
static inline bool handle_error(int status, const char *message) {
    if (status == SUCCESS)
        return true;
    dprintf(STDERR_FILENO, "\033[1;31m%s\033[0m: %s - %s\n", message,
        ERROR(status), GET_ERRNO());
    return false;
}

#endif
