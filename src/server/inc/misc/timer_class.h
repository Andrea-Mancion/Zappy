/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Server side - timer class
*/

#ifndef ZAPPY_TIMER_H_

    #define ZAPPY_TIMER_H_

    #include <sys/time.h>

// Timer class
typedef struct timer_millis_s {
    int time_unit;
    long long int start_time;
    long long int (*tick)(struct timer_millis_s *timer);
    void (*start)(struct timer_millis_s *timer);
    long long int (*get_elapsed_time)(struct timer_millis_s *timer);
    void (*destroy)(struct timer_millis_s *timer);
} timer_millis_t;

// Timer ctor, dtor and methods
int timer_init(timer_millis_t *timer, int frequency);
void timer_destroy(timer_millis_t *timer);
long long int timer_millis_tick(timer_millis_t *timer);
void timer_start(timer_millis_t *timer);
long long int timer_get_elapsed_time(timer_millis_t *timer);

#endif
