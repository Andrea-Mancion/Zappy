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
        int _inventoryId;
        std::vector<std::string> _inventoryNames;
        std::vector<std::pair<sf::Texture *, sf::Sprite *>> _inventorySprites;
        std::vector<std::string> _teamName;
        std::vector<std::pair<int, std::string>> _broadcastList;
        std::vector<std::string> _leaderboard;
        sf::Texture _papyrus_texture;
        sf::Sprite _papyrus_sprite;
        sf::Font _font;
        float _zoom = 1;

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
        void drawMap(sf::RenderWindow &window, float zoomLevel);
        void drawResources(sf::RenderWindow &window);
        void draw_players(sf::RenderWindow &window);
        void drawInventory(sf::RenderWindow &window);
        void inventoryDisplay(sf::RenderWindow &window);
        void setDisplayInventory(bool value);
        void addTeamName(std::string name);
        std::vector<std::string> getTeamNames();
        void addToBroadcastList(std::string elem, int id);
        std::vector<std::pair<int, std::string>> getBroadCastList();
        std::vector<std::string> getLeaderboard();
        void setLeaderboard(std::vector<std::string> leaderboard);
        void drawBroadcast(sf::RenderWindow &window);
        void drawLeaderboard(sf::RenderWindow &window);
        void setZoom(float value);
        float getZoom() const;
};

// sf::Sprite createSprite(const std::string &filename, float scale);
