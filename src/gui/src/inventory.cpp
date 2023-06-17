/*
** EPITECH PROJECT, 2023
** inventory.cpp
** File description:
** inventory
*/

#include "inventory.hpp"

std::vector<std::string> split(std::string str, char delim)
{
    std::vector<std::string> tokens;
    size_t pos = 0;

    while ((pos = str.find(delim)) != std::string::npos)
    {
        tokens.push_back(str.substr(0, pos));
        str.erase(0, pos + 1);
    }
    return tokens;
}

Inventory::Inventory()
{
    _food = 0;
    _linemate = 0;
}

Inventory::~Inventory()
{
}

std::vector<std::pair<Stones, unsigned int>> Inventory::getItems() const
{
    std::vector<std::pair<Stones, unsigned int>> items;

    items.push_back(std::make_pair(FOOD, _food));
    items.push_back(std::make_pair(LINEMATE, _linemate));
    items.push_back(std::make_pair(DERAUMERE, _deraumere));
    items.push_back(std::make_pair(SIBUR, _sibur));
    items.push_back(std::make_pair(MENDIANE, _mendiane));
    items.push_back(std::make_pair(PHIRAS, _phiras));
    items.push_back(std::make_pair(THYSTAME, _thystame));
    return items;
}

unsigned int Inventory::getItem(Stones stone) const
{
    switch (stone) {
        case FOOD:
            return _food;
        case LINEMATE:
            return _linemate;
        case DERAUMERE:
            return _deraumere;
        case SIBUR:
            return _sibur;
        case MENDIANE:
            return _mendiane;
        case PHIRAS:
            return _phiras;
        case THYSTAME:
            return _thystame;
    }
}

void Inventory::setItems(std::string str)
{
    std::vector<std::string> items = split(str, ' ');

    _food = std::stoi(items[0]);
    _linemate = std::stoi(items[1]);
    _deraumere = std::stoi(items[2]);
    _sibur = std::stoi(items[3]);
    _mendiane = std::stoi(items[4]);
    _phiras = std::stoi(items[5]);
    _thystame = std::stoi(items[6]);
}

void Inventory::setItem(Stones stone, unsigned int quantity)
{
    switch (stone) {
        case FOOD:
            _food = quantity;
            break;
        case LINEMATE:
            _linemate = quantity;
            break;
        case DERAUMERE:
            _deraumere = quantity;
            break;
        case SIBUR:
            _sibur = quantity;
            break;
        case MENDIANE:
            _mendiane = quantity;
            break;
        case PHIRAS:
            _phiras = quantity;
            break;
        case THYSTAME:
            _thystame = quantity;
            break;
    }
}
