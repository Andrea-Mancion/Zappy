/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** timer
*/

#include "zappy_misc.h"
#include "misc/timer_class.h"

// Returns the current timestamp in microseconds
long long int timer_millis_tick(ATTR_UNUSED timer_millis_t *timer)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1e6 + tv.tv_usec;
}

// Sets the timer's start time
void timer_start(timer_millis_t *timer)
{
    timer->start_time = timer_millis_tick(timer);
}

// Returns the elapsed time since the timer's start
long long int timer_get_elapsed_time(timer_millis_t *timer)
{
    return timer_millis_tick(timer) - timer->start_time;
}
