/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** list
*/

#ifndef ZAPPY_LIST_H_

    #define ZAPPY_LIST_H_

    #include "zappy_misc.h"

// Node structure for the linked list
typedef struct node_s {
    void *data;
    struct node_s *next;
} node_t;

// List class
typedef struct list_s {
    node_t *head;
    int size;
    bool (*add)(struct list_s *list, void *data);
    void *(*get)(struct list_s *list, int index);
    void (*remove)(struct list_s *list, int index);
    void (*destroy)(struct list_s *list);
} list_t;

// List ctor, dtor and methods
int list_init(list_t *list);
bool list_add(list_t *list, void *data);
void *list_get(list_t *list, int index);
void list_remove(list_t *list, int index);
void list_destroy(list_t *list);

#endif
