/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** list
*/

#include "zappy_misc.h"
#include "misc/list_class.h"

// Adds a list_node to the list, returns false if it fails
bool list_add(list_t *list, void *data)
{
    list_node_t *list_node = malloc(sizeof(list_node_t));
    list_node_t *tmp = list->head;

    if (!list_node)
        return false;
    *list_node = (list_node_t){data, NULL};
    if (!tmp) {
        list->head = list_node;
        list->size++;
        return true;
    }
    for (; tmp->next; tmp = tmp->next);
    tmp->next = list_node;
    list->size++;
    return true;
}

// Inserts a list_node to the list at the given index
bool list_insert(list_t *list, void *data, int index)
{
    list_node_t *list_node = malloc(sizeof(list_node_t)),
    *tmp = list->head, *prev = NULL;
    if (!list_node)
        return false;
    *list_node = (list_node_t){data, NULL};
    if (index == 0) {
        list_node->next = list->head;
        list->head = list_node;
        list->size++;
        return true;
    }
    for (int i = 0; i < index && tmp && tmp->next; i++) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (prev)
        prev->next = list_node;
    list_node->next = tmp;
    list->size++;
    return true;
}

// Gets the index of a list_node from the list
int list_index(list_t *list, void *data)
{
    list_node_t *tmp = list->head;

    for (int i = 0; tmp; i++) {
        if (list->item_cmp(tmp->data, data) == 0)
            return i;
        tmp = tmp->next;
    }
    return -1;
}

// Gets a list_node from the list
void *list_get(list_t *list, int index)
{
    list_node_t *tmp = list->head;

    if (index < 0 || index >= list->size || !tmp)
        return NULL;
    for (int i = 0; i < index && tmp && tmp->next; i++)
        tmp = tmp->next;
    return tmp->data;
}

// Removes a list_node from the list (the data is not freed)
void list_remove(list_t *list, int index)
{
    list_node_t *tmp = list->head;
    list_node_t *prev = NULL;

    if (index < 0 || index >= list->size || !tmp)
        return;
    for (int i = 0; i < index && tmp && tmp->next; i++) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (prev)
        prev->next = tmp->next;
    else
        list->head = tmp->next;
    if (list->item_dtor)
        list->item_dtor(tmp->data);
    free(tmp->data);
    free(tmp);
    list->size--;
}
