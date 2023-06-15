/*
** EPITECH PROJECT, 2023
** map.hpp
** File description:
** map
*/

#pragma once
#include "inventory.hpp"
#define MAP_RANGE 10

typedef enum {
    N,
    E,
    S,
    W
}Orientation_e;

class Player {
    private:
    std::pair<size_t, size_t> _pos;
    Inventory _inv;
    size_t _level;
    size_t _orientation;
    std::string _team;
    size_t id;

    public:
    Player();
    Player(size_t id);
    Player(size_t x, size_t y);
    Player(size_t x, size_t y, size_t id);
    ~Player();
    std::pair<size_t, size_t> getPos() const;
    void setPos(size_t x, size_t y);
    void setPos(std::pair<size_t, size_t> pos);
    size_t getLevel() const;
    void setLevel(size_t level);
    std::string getTeam() const;
    void setTeam(std::string name);
    Orientation_e getOrientation() const;
    void setOrientation(size_t angle);
    void setOrientation(Orientation_e angle);
    Inventory getInventory() const;
    void setInventory(Inventory inv);
    size_t getId() const;
    void setId(size_t id);
};