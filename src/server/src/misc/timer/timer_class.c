/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** timer
*/

#include "zappy_misc.h"
#include "misc/timer_class.h"

// Initial structure of timer
static const timer_millis_t default_timer = {
    .time_unit = 0,
    .start_time = 0,
    .start = &timer_start,
    .tick = &timer_millis_tick,
    .get_elapsed_time = &timer_get_elapsed_time,
    .destroy = &timer_destroy,
};

// Timer constructor
int timer_init(timer_millis_t *timer, int frequency)
{
    *timer = default_timer;
    frequency = frequency < 0.0001 ? 0.0001 : frequency;
    timer->time_unit = 1e6 / frequency;
    return SUCCESS;
}

// Timer destructor
void timer_destroy(ATTR_UNUSED timer_millis_t *timer)
{
}
