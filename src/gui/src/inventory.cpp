/*
** EPITECH PROJECT, 2023
** inventory.cpp
** File description:
** inventory
*/

#include "../inc/inventory.hpp"

std::vector<std::string> split(std::string str, char delim)
{
    std::vector<std::string> tokens;
    size_t pos = 0;

    while ((pos = str.find(delim)) != std::string::npos) {
        tokens.push_back(str.substr(0, pos));
        str.erase(0, pos + 1);
    }
    return tokens;
}

Inventory::Inventory()
{
    this->_food = 0;
    this->_linemate = 0;
    this->_deraumere = 0;
    this->_mendiane = 0;
    this->_phiras = 0;
    this->_sibur = 0;
    this->_thystame = 0;
}

std::vector<std::pair<Stones, unsigned int>> Inventory::getItems() const
{
    std::vector<std::pair<Stones, unsigned int>> items;

    items.push_back(std::make_pair(Stones::FOOD, this->_food));
    items.push_back(std::make_pair(Stones::LINEMATE, this->_linemate));
    items.push_back(std::make_pair(Stones::DERAUMERE, this->_deraumere));
    items.push_back(std::make_pair(Stones::SIBUR, this->_sibur));
    items.push_back(std::make_pair(Stones::MENDIANE, this->_mendiane));
    items.push_back(std::make_pair(Stones::PHIRAS, this->_phiras));
    items.push_back(std::make_pair(Stones::THYSTAME, this->_thystame));
    return items;
}

unsigned int Inventory::getItem(Stones stone) const
{
    switch (stone) {
        case Stones::FOOD:
            return this->_food;
        case Stones::LINEMATE:
            return this->_linemate;
        case Stones::DERAUMERE:
            return this->_deraumere;
        case Stones::SIBUR:
            return this->_sibur;
        case Stones::MENDIANE:
            return this->_mendiane;
        case Stones::PHIRAS:
            return this->_phiras;
        case Stones::THYSTAME:
            return this->_thystame;
    }
    return 0;
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
        case Stones::FOOD:
            this->_food = quantity;
            break;
        case Stones::LINEMATE:
            this->_linemate = quantity;
            break;
        case Stones::DERAUMERE:
            this->_deraumere = quantity;
            break;
        case Stones::SIBUR:
            this->_sibur = quantity;
            break;
        case Stones::MENDIANE:
            this->_mendiane = quantity;
            break;
        case Stones::PHIRAS:
            this->_phiras = quantity;
            break;
        case Stones::THYSTAME:
            this->_thystame = quantity;
            break;
    }
}
