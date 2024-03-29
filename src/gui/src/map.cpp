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

    _inventoryNames = std::vector<std::string>{"food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};
    _inventorySprites = std::vector<std::pair<sf::Texture *, sf::Sprite *>>();
    for (size_t i = 0; i < _inventoryNames.size(); i++) {
        sf::Texture *texture = new sf::Texture();
        sf::Sprite *sprite = new sf::Sprite();
        texture->loadFromFile("assets/" + _inventoryNames[i] + ".png");
        sprite->setTexture(*texture);
        sprite->setScale(sf::Vector2f(0.10f, 0.10f));
        _inventorySprites.push_back(std::pair<sf::Texture *, sf::Sprite *>(texture, sprite));
    _papyrus_texture = sf::Texture();
    _papyrus_sprite = sf::Sprite();
    _papyrus_texture.loadFromFile("assets/papyrus.png");
    _papyrus_sprite.setTexture(_papyrus_texture);
    _papyrus_sprite.setScale(sf::Vector2f(1.0f, 2.3f));
    _font.loadFromFile("assets/Cookie-Regular.ttf");
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

void Map::drawMap(sf::RenderWindow& window, float zoomLevel)
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::Vector2u size(desktopMode.width, desktopMode.height);
    //sf::Vector2u size = window.getSize();
    sf::FloatRect bounds = this->_sprite.getGlobalBounds();
    Inventory *tile = nullptr;
    float isoX = 0.0f;
    float isoY = 0.0f;

    for (size_t i = 0; i < this->_dimension.first; i++) {
        for (size_t j = 0; j < this->_dimension.second; j++) {
            if ((int)((int)i - (int)j) < 0)
                isoX = -(i - j) * 0.5f * -(bounds.width / 2) + size.x / 2;
            else
                isoX = (i - j) * 0.5f * (bounds.width / 2) + size.x / 2;
            isoY = (i + j) * 0.4f * (bounds.height / 2) + size.y / 3;

            this->_sprite.setPosition((int)isoX, (int)isoY);
            window.draw(this->_sprite);
        }
    }
}

void Map::drawResources(sf::RenderWindow& window)
{
    sf::Vector2u size = window.getSize();
    sf::FloatRect bounds = this->_sprite.getGlobalBounds();
    Inventory *tile = nullptr;
    float isoX = 0.0f;
    float isoY = 0.0f;

    for (size_t i = 0; i < this->_dimension.first; i++) {
        for (size_t j = 0; j < this->_dimension.second; j++) {
            if ((int)((int)i - (int)j) < 0)
                isoX = -(i + 1 - j) * 0.5f * -(bounds.width / 2) + size.x / 2;
            else
                isoX = (i + 1 - j) * 0.5f * (bounds.width / 2) + size.x / 2;
            isoY = (i + 1 + j) * 0.4f * (bounds.height / 2) + size.y / 3;
            tile = &this->_tiles[i][j];
            for (size_t item = 0; item <= this->_inventoryNames.size(); item++)
            {
                if (tile->getItem((Stones)(item)) > 0)
                {
                    this->_inventorySprites[item].second->setPosition((int)isoX, (int)isoY);
                    window.draw(*this->_inventorySprites[item].second);
                }
            }
        }
    }
}

void Map::draw_players(sf::RenderWindow & window)
{
    sf::Vector2u size = window.getSize();
    sf::FloatRect bounds = this->_sprite.getGlobalBounds();
    std::pair<size_t, size_t> player = std::pair<size_t, size_t>(0, 0);
    float isoX = 0.0f;
    float isoY = 0.0f;
    sf::Text text;
    sf::Font font;

    font.loadFromFile("assets/YsabeauSC.ttf");
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(0.8);
    text.setOutlineColor(sf::Color::Black);
    text.setCharacterSize(15);
    for (size_t i = 0; i < this->_players.size(); i++) {
        player = this->_players[i].getPos();
        if ((int)((int)player.first - (int)player.second) < 0)
            isoX = -(player.first - player.second) * 0.5f * - (bounds.width / 2) + size.x / 2;
        else
            isoX = (player.first - player.second) * 0.4f * (bounds.width / 2) + size.x / 2;
        isoY = ((player.first + player.second) * 0.4f * (bounds.height / 2) + size.y / 3) + 5;
        this->_players[i].getSprite()->setPosition((int)isoX, (int)isoY);
        this->_players[i].updateSpriteFrame();
        text.setString(this->_players[i].getTeam().c_str());
        text.setPosition((int)isoX, (int)isoY);
        this->_players[i].draw(window);
        window.draw(text);
    }
}

void Map::setDisplayInventory(bool isInventoryOpen)
{
    this->_isInventoryOpen = isInventoryOpen;
}

void Map::drawInventory(sf::RenderWindow &window)
{
    sf::Vector2u size = window.getSize();
    sf::FloatRect view = window.getView().getViewport();
    Inventory playerInventory = this->_players[this->_inventoryId].getInventory();
    sf::Text amount;
    float isoX = 0.0f;
    float isoY = 0.0f;

    amount.setFont(this->_font);
    amount.setFillColor(sf::Color::Black);
    this->_papyrus_sprite.setPosition(window.mapPixelToCoords(sf::Vector2i(view.left, view.top)));
    this->_papyrus_sprite.setScale(sf::Vector2f(1.0f * this->_zoom, 2.3f * this->_zoom));
    window.draw(this->_papyrus_sprite);
    amount.setString((std::string)("Level : " + std::to_string(this->_players[this->_inventoryId].getLevel())).c_str());
    amount.setPosition(window.mapPixelToCoords(sf::Vector2i(view.left + 60, view.top + 35)));
    amount.setCharacterSize((unsigned int)((float)30 * this->_zoom));
    window.draw(amount);
    for (size_t i = 0; i < this->_inventoryNames.size(); i++) {
        unsigned int itemAmount = playerInventory.getItem((Stones)i);
        this->_inventorySprites[i].second->setPosition(window.mapPixelToCoords(sf::Vector2i(view.left + 50, view.top + 110 + i * 50)));
        this->_inventorySprites[i].second->setScale(0.10f * this->_zoom, 0.10f * this->_zoom);
        window.draw(*this->_inventorySprites[i].second);
        this->_inventorySprites[i].second->setScale(sf::Vector2f(0.10f, 0.10f));
        amount.setCharacterSize((unsigned int)((float)26 * this->_zoom));
        amount.setString(" : " + std::to_string(itemAmount));
        amount.setPosition(window.mapPixelToCoords(sf::Vector2i(view.left + 75, view.top + 100 + i * 50)));
        window.draw(amount);
    }
}

void Map::inventoryDisplay(sf::RenderWindow & window)
{
    sf::Mouse mouse;
    sf::Vector2i mousePos = mouse.getPosition(window);

    if (this->_isInventoryOpen == true) {
        drawInventory(window);
        return;
    }
    for (size_t i = 0; i < this->_players.size(); i++) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (this->_players[i].getSprite()->getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                this->_inventoryId = i;
                this->_isInventoryOpen = true;
                drawInventory(window);
                return;
            }
        }
    }

}

std::vector<std::string> Map::getTeamNames()
{
    return this->_teamName;
}

void Map::setZoom(float value)
{
    this->_zoom = value;
}

float Map::getZoom() const
{
    return this->_zoom;
}

void Map::addTeamName(std::string name)
{
    if (std::find(this->_teamName.begin(), this->_teamName.end(), name) == this->_teamName.end())
        this->_teamName.push_back(name);
}

std::vector<std::pair<int, std::string>> Map::getBroadCastList()
{
    return this->_broadcastList;
}

void Map::addToBroadcastList(std::string elem, int id)
{
    if (this->_broadcastList.size() < 5) {
        this->_broadcastList.push_back(std::make_pair(id, elem));
    } else if (this->_broadcastList.size() >= 5) {
        this->_broadcastList.erase(this->_broadcastList.begin());
        this->_broadcastList.push_back(std::make_pair(id, elem));
    }
}

std::vector<std::string> Map::getLeaderboard()
{
    return this->_leaderboard;
}

void Map::setLeaderboard(std::vector<std::string> leaderboard)
{
    this->_leaderboard = leaderboard;
}

void Map::drawLeaderboard(sf::RenderWindow &window)
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::Vector2u desktopSize(desktopMode.width, desktopMode.height);
    sf::Text text;
    sf::Font font;

    font.loadFromFile("assets/YsabeauSC.ttf");
    text.setFont(font);
    text.setString("Leaderboard:");
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize((unsigned int)((float)26 * this->_zoom));
    text.setPosition(window.mapPixelToCoords(sf::Vector2i(25, desktopSize.y - this->getLeaderboard().size() * 25 - 105)));
    text.setStyle(sf::Text::Underlined);
    window.draw(text);
    for (size_t i = 0; i < this->getLeaderboard().size(); i++) {
        sf::Text text;
        std::string str = "  " + std::to_string(i + 1) + ": " + this->getLeaderboard().at(i);
        text.setFont(this->_font);
        text.setFillColor(sf::Color::Black);
        text.setString(str.c_str());
        text.setCharacterSize((unsigned int)((float)24 * this->_zoom));
        text.setPosition(window.mapPixelToCoords(sf::Vector2i(25, desktopSize.y - 125 + 25 * i)));
        window.draw(text);
    }
}

void Map::drawBroadcast(sf::RenderWindow &window)
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::Vector2u desktopSize(desktopMode.width, desktopMode.height);
    sf::Text text;
    sf::Font font;
    std::vector<std::pair<int, std::string>> broadcast = this->getBroadCastList();
    std::vector<Player> *playerList = this->getPlayers();

    font.loadFromFile("assets/YsabeauSC.ttf");
    text.setFont(font);
    text.setString("Messages: ");
    text.setFillColor(sf::Color::White);
    text.setCharacterSize((unsigned int)((float)26 * this->_zoom));
    text.setPosition(window.mapPixelToCoords(sf::Vector2i(desktopSize.x - 375, desktopSize.y - 390)));
    text.setStyle(sf::Text::Underlined);
    window.draw(text);
    for (size_t i = 0; i < broadcast.size(); i++) {
        sf::Text text;
        std::string str = "Player " + std::to_string(playerList->at(broadcast.at(i).first).getId()) + ": " + broadcast.at(i).second;
        text.setFont(this->_font);
        text.setFillColor(sf::Color::White);
        text.setString(str.c_str());
        text.setCharacterSize((unsigned int)((float)12 * this->_zoom));
        text.setPosition(window.mapPixelToCoords(sf::Vector2i(desktopSize.x - 375, desktopSize.y - 320 + 10 * i)));
        window.draw(text);
    }
}