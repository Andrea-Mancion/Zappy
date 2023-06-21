/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** map
*/

#include "zappy_misc.h"
#include "misc/map_class.h"

// Adds a map_node to the map, returns false if it fails
bool map_set(map_t *map, void *key, void *data)
{
    map_node_t *map_node = malloc(sizeof(map_node_t));
    map_node_t *tmp = map->head;

    if (!map_node)
        return false;
    *map_node = (map_node_t){key, data, NULL};
    if (!tmp) {
        map->head = map_node;
        return true;
    }
    for (; tmp->next; tmp = tmp->next);
    tmp->next = map_node;
    return true;
}

// Gets a map_node from the map
void *map_get(map_t *map, void *index)
{
    map_node_t *tmp = map->head;

    if (!tmp)
        return NULL;
    for (; tmp; tmp = tmp->next)
        if (map->key_cmp(tmp->key, index) == 0)
            return tmp->data;
    return NULL;
}

// Removes a map_node from the map (the data is not freed)
void map_remove(map_t *map, void *index)
{
    map_node_t *tmp = map->head;
    map_node_t *prev = NULL;

    for (; tmp && tmp->next; tmp = tmp->next)
        if (map->key_cmp(tmp->key, index) == 0)
            break;
    if (prev)
        prev->next = tmp->next;
    else
        map->head = tmp->next;
    free(tmp);
}
