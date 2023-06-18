/*
** EPITECH PROJECT, 2023
** map.cpp
** File description:
** window and map
*/

#include "../inc/gui.hpp"

void clearWindow(sf::RenderWindow& window, const sf::Color& backgroundColor)
{
    window.clear(backgroundColor);
}

void displayWindow(sf::RenderWindow& window)
{
    window.display();
}

void drawSprite(sf::RenderWindow& window, const sf::Sprite& sprite)
{
    window.draw(sprite);
}

sf::Sprite createSprite(const std::string& filename, float scale)
{
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        throw std::runtime_error("Failed to load texture: " + filename);
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(scale, scale);

    return sprite;
}

void draw_map(sf::RenderWindow& window, sf::Sprite& sprite, sf::Sprite& playerSprite)
{
    sf::Vector2u size = window.getSize();
    sf::FloatRect bounds = sprite.getGlobalBounds();
    float isoX = 0.0f;
    float isoY = 0.0f;

    sf::Color backgroundColor(176, 224, 230);
    clearWindow(window, backgroundColor);

    for (size_t i = 0; i < MAP_RANGE; i++)
    {
        for (size_t j = 0; j < MAP_RANGE; j++)
        {
            isoX = (i - j) * 0.5f * (bounds.width / 2) + size.x / 2;
            isoY = (i + j) * 0.4f * (bounds.height / 2) + size.y / 4;

            sprite.setPosition((int)isoX, (int)isoY);
            drawSprite(window, sprite);

            isoX = (i - j) * 0.5f * -(bounds.width / 2) + size.x / 2;
            sprite.setPosition((int)isoX, (int)isoY);
            drawSprite(window, sprite);
        }
    }
    drawSprite(window, playerSprite);
    displayWindow(window);
}

// sf::Sprite createSprite(std::string path, float scale)
// {
//     sf::Texture texture;
//     if (!texture.loadFromFile((std::string)path)) {
//         std::cerr << "Error: could not load texture: " << path << std::endl;
//         exit(84);
//     }
//     sf::Sprite sprite;
//     sprite.setTexture(texture);
//     sprite.setScale(scale, scale);
//     return sprite;
// }

////////////////////////////////////////////

Map::Map()
{
    _dimension = std::pair<unsigned int, unsigned int>(0, 0);
    _tiles = std::vector<std::vector<Inventory>>();
    _players = std::vector<Player>();
}

Map::Map(unsigned int width, unsigned int heigth, std::vector<std::vector<Inventory>> tiles)
{
    _dimension = std::pair<unsigned int, unsigned int>(width, heigth);
    _tiles = tiles;
    _players = std::vector<Player>();
}

Map::~Map()
{
}

void Map::setDimension(int width, int heigth)
{
    _dimension.first = width;
    _dimension.second = heigth;
}

std::pair<unsigned int, unsigned int> Map::getDimension() const
{
    return _dimension;
}

Player *Map::getPlayer(size_t id)
{
    return &this->_players[id];
}

void Map::addPlayer(Player player)
{
    _players.push_back(player);
}

std::vector<Player> *Map::getPlayers()
{
    return &this->_players;
}

std::vector<std::vector<Inventory>> *Map::getTiles()
{
    return &this->_tiles;
}

Inventory *Map::getTile(size_t x, size_t y)
{
    return &this->_tiles[x][y];
}

void Map::setTiles(std::vector<std::vector<Inventory>> tiles)
{
    this->_tiles = tiles;
}

void Map::setTile(size_t x, size_t y, Inventory tile)
{
    this->_tiles[x][y] = tile;
}
