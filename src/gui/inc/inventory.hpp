/*
** EPITECH PROJECT, 2023
** inventory.hpp
** File description:
** store items and quantity in a variable
*/

#pragma once

#include <utility>
#include <vector>
#include <string>

#include "libs.hpp"

typedef enum {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
} Stones;

class Inventory {
    private:
    unsigned int _food;
    unsigned int _linemate;
    unsigned int _deraumere;
    unsigned int _sibur;
    unsigned int _mendiane;
    unsigned int _phiras;
    unsigned int _thystame;
    std::size_t _typeQuantity = 7;

    public:
    Inventory();
    ~Inventory();
    std::vector<std::pair<Stones, unsigned int>> getItems() const;
    unsigned int getItem(Stones stone) const;
    void setItems(std::string str);
    void setItem(Stones stone, unsigned int quantity);
};
