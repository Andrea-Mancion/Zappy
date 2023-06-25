/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** list
*/

#ifndef ZAPPY_LIST_H_

    #define ZAPPY_LIST_H_

    #include "zappy_misc.h"

    #define IS_EQUAL_CMP(x, y) (x - y)

// Node structure for the linked list
typedef struct list_node_s {
    void *data;
    struct list_node_s *next;
} list_node_t;

// List class
typedef struct list_s {
    list_node_t *head;
    int size;
    bool (*add)(struct list_s *list, void *data);
    bool (*insert)(struct list_s *list, void *data, int index);
    void *(*get)(struct list_s *list, int index);
    int (*index)(struct list_s *list, void *data);
    void (*remove)(struct list_s *list, int index);
    void (*destroy)(struct list_s *list);
    void (*item_dtor)(void *);
    int (*item_cmp)(void *, void *);
} list_t;

// Default structure of list
extern const list_t default_list;

// List ctor, dtor and methods
int list_init(list_t *list, void (*item_dtor)(void *), int (*item_cmp)(void *,
    void *));
bool list_add(list_t *list, void *data);
bool list_insert(list_t *list, void *data, int index);
void *list_get(list_t *list, int index);
int list_index(list_t *list, void *data);
void list_remove(list_t *list, int index);
void list_destroy(list_t *list);

#endif
