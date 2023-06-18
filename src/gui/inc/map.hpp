/*
** EPITECH PROJECT, 2023
** map.hpp
** File description:
** map
*/

#pragma once

#include "libs.hpp"
#include "inventory.hpp"
#include "player.hpp"

class Map {
    private:
        std::pair<unsigned int, unsigned int> _dimension;
        std::vector<std::vector<Inventory>> _tiles;
        std::vector<Player> _players;

    public:
        Map();
        Map(unsigned int width, unsigned int heigth, std::vector<std::vector<Inventory>> tiles);
        ~Map();
        void setDimension(int width, int heigth);
        std::pair<unsigned int, unsigned int> getDimension() const;
        Player *getPlayer(size_t id);
        std::vector<Player> *getPlayers();
        void addPlayer(Player player);
        std::vector<std::vector<Inventory>> *getTiles();
        Inventory *getTile(size_t x, size_t y);
        void setTiles(std::vector<std::vector<Inventory>>);
        void setTile(size_t x, size_t y, Inventory tile);
};

void draw_map(sf::RenderWindow& window, sf::Sprite& sprite, sf::Sprite& playerSprite);
sf::Sprite createSprite(const std::string& filename, float scale);
void drawSprite(sf::RenderWindow& window, const sf::Sprite& sprite);
void displayWindow(sf::RenderWindow& window);
void clearWindow(sf::RenderWindow& window, const sf::Color& backgroundColor);
