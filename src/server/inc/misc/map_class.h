/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** map
*/

#ifndef ZAPPY_MAP_H_

    #define ZAPPY_MAP_H_

    #include "zappy_misc.h"

// Node structure for the linked map
typedef struct map_node_s {
    void *key;
    void *data;
    struct map_node_s *next;
} map_node_t;

// Map class
typedef struct map_s {
    map_node_t *head;
    bool (*set)(struct map_s *map, void *key, void *data);
    void *(*get)(struct map_s *map, void *key);
    void (*remove)(struct map_s *map, void *key);
    void (*destroy)(struct map_s *map);
    int (*key_cmp)(void *, void *);
    void (*key_dtor)(void *);
    void (*val_dtor)(void *);
} map_t;

// Map ctor, dtor and methods
int map_init(map_t *map, void (*key_dtor)(void *), void (*val_dtor)(void *),
    int (*key_cmp)(void *, void *));
bool map_set(map_t *map, void *key, void *data);
void *map_get(map_t *map, void *key);
void map_remove(map_t *map, void *key);
void map_destroy(map_t *map);

#endif
