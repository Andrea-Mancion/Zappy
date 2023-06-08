/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** list
*/

#include "zappy_misc.h"
#include "misc/list_class.h"

// Adds a node to the list, returns false if it fails
bool list_add(list_t *list, void *data)
{
    node_t *node = malloc(sizeof(node_t));
    node_t *tmp = list->head;

    if (!node)
        return false;
    *node = (node_t){data, list->head};
    if (!tmp) {
        list->head = node;
        list->size++;
        return true;
    }
    for (; tmp->next; tmp = tmp->next);
    tmp->next = node;
    list->size++;
    return true;
}

// Gets a node from the list
void *list_get(list_t *list, int index)
{
    node_t *tmp = list->head;

    if (index < 0 || index >= list->size || !tmp)
        return NULL;
    for (int i = 0; i < index && tmp && tmp->next; i++)
        tmp = tmp->next;
    return tmp->data;
}

// Removes a node from the list (the data is not freed)
void list_remove(list_t *list, int index)
{
    node_t *tmp = list->head;
    node_t *prev = NULL;

    for (int i = 0; i < index && tmp && tmp->next; i++) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (prev)
        prev->next = tmp->next;
    else
        list->head = tmp->next;
    free(tmp);
    list->size--;
}
