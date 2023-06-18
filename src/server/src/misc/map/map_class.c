/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** map
*/

#include "zappy_misc.h"
#include "misc/map_class.h"

// Initial structure of map
const map_t default_game_map = {
    .head = NULL,
    .set = &map_set,
    .remove = &map_remove,
    .get = &map_get,
    .destroy = &map_destroy,
    .key_dtor = NULL,
    .val_dtor = NULL,
    .key_cmp = NULL,
};

// map constructor
int map_init(map_t *map, void (*key_dtor)(void *), void (*val_dtor)(void *),
    int (*key_cmp)(void *, void *))
{
    *map = default_game_map;
    map->key_cmp = key_cmp;
    map->key_dtor = key_dtor;
    map->val_dtor = val_dtor;
    return SUCCESS;
}

// Destroys the map
void map_destroy(map_t *map)
{
    map_node_t *next = NULL;

    for (map_node_t *tmp = map->head; tmp; tmp = next) {
        if (map->key_dtor)
            map->key_dtor(tmp->key);
        if (map->val_dtor)
            map->val_dtor(tmp->data);
        free(tmp->key);
        free(tmp->data);
        next = tmp->next;
        free(tmp);
    }
}
