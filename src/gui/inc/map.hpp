/*
** EPITECH PROJECT, 2023
** map.hpp
** File description:
** map
*/

#pragma once
#include "player.hpp"
#define MAP_RANGE 10

class Map {
    public:
    unsigned int _width;
    unsigned int _heigth;
    std::vector<std::vector<Inventory>> _tiles;
    std::vector<Player> players;

    private:
    Map();
    ~Map();
    void setDimension(int width, int heigth);
    void setWidth(int width);
    void setHeight(int heigth);
    unsigned int getWidth() const;
    unsigned int getHeigth() const;
    void getPlayer(size_t id);
    void addPlayer(Player player);
};
