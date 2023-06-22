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

    //_inventoryNames = std::vector<std::string>("food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame");
    _inventorySprites = std::vector<std::pair<sf::Texture, sf::Sprite>>();
    for (size_t i = 0; i < _inventoryNames.size(); i++) {
        sf::Texture texture;
        sf::Sprite sprite;
        texture.loadFromFile("assets/" + _inventoryNames[i] + ".png");
        sprite.setTexture(texture);
        sprite.setScale(sf::Vector2f(0.5f, 0.5f));
        _inventorySprites.push_back(std::pair<sf::Texture, sf::Sprite>(texture, sprite));
    }
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

Player *Map::getPlayerFromId(size_t id)
{
    for (int i = 0; this->_players.size(); i++)
        if (this->_players.at(i).getId() == id)
            return &this->_players.at(i);
    return nullptr;
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

void Map::draw_map(sf::RenderWindow& window, float zoomLevel)
{
    sf::Vector2u size = window.getSize();
    sf::FloatRect bounds = this->_sprite.getGlobalBounds();
    float isoX = 0.0f;
    float isoY = 0.0f;

    sf::Color backgroundColor(176, 224, 230);
    window.clear(backgroundColor);

    float centerX = (this->_dimension.first - 1) * 0.5f * (bounds.width / 2);
    float centerY = (this->_dimension.second - 1) * 0.5f * (bounds.height / 2);

    float offsetX = (size.x / 2) - (zoomLevel * centerX);
    float offsetY = (size.y / 2) - (zoomLevel * centerY);

    sf::View view(sf::FloatRect(offsetX, offsetY, size.x / zoomLevel, size.y / zoomLevel));
    view.setCenter(size.x / 2, size.y / 2);
    window.setView(view);

    for (size_t i = 0; i < this->_dimension.second; i++) {
        for (size_t j = 0; j < this->_dimension.first; j++) {
            isoX = (i - j) * 0.5f * (bounds.width / 2) + size.x / 2;
            isoY = (i + j) * 0.4f * (bounds.height / 2) + size.y / 3;

            this->_sprite.setPosition((int)isoX, (int)isoY);
            window.draw(this->_sprite);

            isoX = (i - j) * 0.5f * -(bounds.width / 2) + size.x / 2;
            this->_sprite.setPosition((int)isoX, (int)isoY);
            window.draw(this->_sprite);
        }
    }
}

void Map::setDisplayInventory(bool value, int id)
{
    this->_isInventoryOpen = value;
    this->_displayInventoryId = id;
}

void Map::setDisplayInventory(bool value)
{
    this->_isInventoryOpen = value;
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
        this->_players[i].updateSpriteFrame();
        this->_players[i].draw(window);
    }
}

void Map::inventoryDisplay(sf::RenderWindow &window)
{
    if (this->_isInventoryOpen)
    {
        sf::Texture backgroundTexture;
        if (!backgroundTexture.loadFromFile("assets/inventory/papyrus.png")) {
            std::cerr << "Error: could not load background texture" << std::endl;
            return;
        }
        sf::Sprite backgroundSprite(backgroundTexture);
        sf::Vector2f newSize(200.0f, 300.0f);
        backgroundSprite.setScale(newSize.x / backgroundSprite.getLocalBounds().width,
                                  newSize.y / backgroundSprite.getLocalBounds().height);

        sf::Texture accessoryTexture1;
        if (!accessoryTexture1.loadFromFile("assets/inventory/food/food.png")) {
            std::cerr << "Error: could not load accessory texture" << std::endl;
            return;
        }
        sf::Sprite accessorySprite1(accessoryTexture1);

        sf::Vector2f newAccessorySize(50.0f, 50.0f);
        accessorySprite1.setScale(newAccessorySize.x / accessorySprite1.getLocalBounds().width,
                                  newAccessorySize.y / accessorySprite1.getLocalBounds().height);

        accessorySprite1.setPosition(50.0f, 50.0f);

        sf::Texture accessoryTexture2;
        if (!accessoryTexture2.loadFromFile("assets/inventory/gems/sibur.png"))
        {
            std::cerr << "Error: could not load accessory texture" << std::endl;
            return;
        }
        sf::Sprite accessorySprite2(accessoryTexture2);

        sf::Vector2f newAccessorySize1(40.0f, 50.0f);
        accessorySprite2.setScale(newAccessorySize1.x / accessorySprite2.getLocalBounds().width,
                                  newAccessorySize1.y / accessorySprite2.getLocalBounds().height);

        accessorySprite2.setPosition(100.0f, 50.0f);

        sf::Texture accessoryTexture3;
        if (!accessoryTexture3.loadFromFile("assets/inventory/gems/deraumere.png"))
        {
            std::cerr << "Error: could not load accessory texture" << std::endl;
            return;
        }
        sf::Sprite accessorySprite3(accessoryTexture3);

        sf::Vector2f newAccessorySize2(40.0f, 50.0f);
        accessorySprite3.setScale(newAccessorySize2.x / accessorySprite3.getLocalBounds().width,
                                  newAccessorySize2.y / accessorySprite3.getLocalBounds().height);

        accessorySprite3.setPosition(50.0f, 100.0f);

        window.draw(backgroundSprite);
        window.draw(accessorySprite1);
        window.draw(accessorySprite2);
        window.draw(accessorySprite3);
    }
}
