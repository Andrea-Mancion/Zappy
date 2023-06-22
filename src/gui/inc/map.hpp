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
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::RenderWindow *_window;
        bool _isInventoryOpen = false;
        int _displayInventoryId;
        std::vector<std::string> _inventoryNames;
        std::vector<std::pair<sf::Texture, sf::Sprite>> _inventorySprites;

    public :
        Map();
        Map(unsigned int width, unsigned int heigth, std::string path, sf::RenderWindow *window);
        Map(unsigned int width, unsigned int heigth, std::vector<std::vector<Inventory>> tiles, sf::RenderWindow *window);
        ~Map();
        void setDimension(int width, int heigth);
        std::pair<unsigned int, unsigned int> getDimension() const;
        Player *getPlayer(size_t id);
        Player *getPlayerFromId(size_t id);
        std::vector<Player> *getPlayers();
        void addPlayer(Player player);
        std::vector<std::vector<Inventory>> *getTiles();
        Inventory *getTile(size_t x, size_t y);
        void setTiles(std::vector<std::vector<Inventory>> tiles);
        void draw_map(sf::RenderWindow &window, float zoomLevel);
        void draw_players(sf::RenderWindow &window);
        void inventoryDisplay(sf::RenderWindow &window);
        void setDisplayInventory(bool value, int id);
        void setDisplayInventory(bool value);
};

// sf::Sprite createSprite(const std::string &filename, float scale);
