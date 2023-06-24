/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** list
*/

#include "zappy_misc.h"
#include "misc/list_class.h"

// Initial structure of list
const list_t default_list = {
    .head = NULL,
    .size = 0,
    .add = &list_add,
    .insert = &list_insert,
    .index = &list_index,
    .remove = &list_remove,
    .get = &list_get,
    .destroy = &list_destroy,
    .item_dtor = NULL,
};

// List constructor
int list_init(list_t *list, void (*item_dtor)(void *), int (*item_cmp)(void *,
    void *))
{
    *list = default_list;
    list->item_dtor = item_dtor;
    list->item_cmp = item_cmp;
    return SUCCESS;
}

// List destructor
void list_destroy(list_t *list)
{
    list_node_t *next = NULL;

    for (list_node_t *tmp = list->head; tmp; tmp = next) {
        if (list->item_dtor)
            list->item_dtor(tmp->data);
        free(tmp->data);
        next = tmp->next;
        free(tmp);
    }
}
