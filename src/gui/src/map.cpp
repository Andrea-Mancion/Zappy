/*
** EPITECH PROJECT, 2023
** map.cpp
** File description:
** window and map
*/

#include "../inc/gui.hpp"

Map::Map()
{
    _dimension = std::pair<unsigned int, unsigned int>(0, 0);
    _tiles = std::vector<std::vector<Inventory>>();
    _players = std::vector<Player>();
}

Map::Map(unsigned int width, unsigned int height, std::string path, sf::RenderWindow *window)
{
    _dimension = std::pair<unsigned int, unsigned int>(width, height);
    _tiles = std::vector<std::vector<Inventory>>();
    _players = std::vector<Player>();
    _texture = sf::Texture();
    _window = window;
    _sprite = sf::Sprite();
    if (!_texture.loadFromFile(path)) {
        std::cerr << "Cannot load file " << path << std::endl;
        exit(84);
    }
    sf::Vector2u size = _window->getSize();
    _sprite.setTexture(_texture);
    _sprite.setScale(sf::Vector2f(0.5f, 0.5f));
    // _sprite.setScale(sf::Vector2f(size.x / _texture.getSize().x, size.y / _texture.getSize().y));
}

Map::Map(unsigned int width, unsigned int heigth, std::vector<std::vector<Inventory>> tiles, sf::RenderWindow *window)
{
    _dimension = std::pair<unsigned int, unsigned int>(width, heigth);
    _tiles = tiles;
    _players = std::vector<Player>();
    _window = window;
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
    for (int i = 0; this->_players.size(); i++)
        if (this->_players.at(i).getId() == id)
            return &this->_players.at(i);
    return nullptr;
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

void Map::draw_map(sf::RenderWindow &window)
{
    sf::Vector2u size = window.getSize();
    sf::FloatRect bounds = this->_sprite.getGlobalBounds();
    float isoX = 0.0f;
    float isoY = 0.0f;

    sf::Color backgroundColor(176, 224, 230);
    window.clear(backgroundColor);

    for (size_t i = 0; i < this->_dimension.second; i++)
    {
        for (size_t j = 0; j < this->_dimension.first; j++)
        {
            isoX = (i - j) * 0.5f * (bounds.width / 2) + size.x / 2;
            isoY = (i + j) * 0.4f * (bounds.height / 2) + size.y / 4;

            this->_sprite.setPosition((int)isoX, (int)isoY);
            window.draw(this->_sprite);

            isoX = (i - j) * 0.5f * -(bounds.width / 2) + size.x / 2;
            this->_sprite.setPosition((int)isoX, (int)isoY);
            window.draw(this->_sprite);
        }
    }
}

void Map::draw_players(sf::RenderWindow &window)
{
    sf::Vector2u size = window.getSize();
    sf::FloatRect bounds = this->_sprite.getGlobalBounds();
    std::pair<size_t, size_t> player = std::pair<size_t, size_t>(0, 0);
    float isoX = 0.0f;
    float isoY = 0.0f;

    for (size_t i = 0; i < this->_players.size(); i++)
    {
        player = this->_players[i].getPos();
        if ((int)((int)player.first - (int)player.second) < 0) {
            isoX = -(player.first - player.second) * 0.5f * -(bounds.width / 2) + size.x / 2;
        } else
            isoX = (player.first - player.second) * 0.5f * (bounds.width / 2) + size.x / 2;
        isoY = (player.first + player.second) * 0.4f * (bounds.height / 2) + size.y / 4;

        std::cout << "x: " << isoX << " y: " << isoY << std::endl;
        this->_players[i].getSprite()->setPosition((int)isoX, (int)isoY);
        this->_players[i].draw(window);
    }
}

void Map::inventoryDisplay(sf::RenderWindow &window)
{
    sf::Mouse mouse;
    sf::Keyboard keyboard;
    bool isInventoryOpen = false;

    if (mouse.isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i pos = mouse.getPosition(window);
        for (size_t i = 0; i < this->_players.size(); i++) {
            if (this->_players[i].getSprite()->getGlobalBounds().contains(pos.x, pos.y)) {
                isInventoryOpen = true;
                break;
            }
        }
    }
    if (isInventoryOpen) {
        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("assets/inventory/papyrus.png")) {
            std::cerr << "Error: could not load background texture" << std::endl;
            return;
        }
        sf::Sprite backgroundSprite(backgroundTexture);

        sf::Texture accessoryTexture1;
        if (!accessoryTexture1.loadFromFile("assets/inventory/food/food.png")) {
            std::cerr << "Error: could not load accessory texture" << std::endl;
            return;
        }
        sf::Sprite accessorySprite1(accessoryTexture1);

        while (isInventoryOpen) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return;
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    isInventoryOpen = false;
                    break;
                }
            }
            window.clear();
            window.draw(backgroundSprite);
            window.draw(accessorySprite1);
            window.display();
        }
    }
}
