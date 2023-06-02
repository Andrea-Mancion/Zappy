/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** list
*/

#include "classes/list_class.h"

// Initial structure of list
static const list_t default_list = {
    .head = NULL,
    .size = 0,
    .add = &list_add,
    .remove = &list_remove,
    .get = &list_get,
    .destroy = &list_destroy,
};

// List constructor
int list_init(list_t *list)
{
    *list = default_list;
    return SUCCESS;
}

// Destroys the list
void list_destroy(list_t *list)
{
    node_t *next = NULL;

    for (node_t *tmp = list->head; tmp; tmp = next) {
        next = tmp->next;
        free(tmp);
    }
}
