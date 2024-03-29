/*
** EPITECH PROJECT, 2023
** player.hpp
** File description:
** player
*/

#include "libs.hpp"
#include "inventory.hpp"

typedef enum {
    N,
    E,
    S,
    W
} Orientation_e;

class Player {
    private:
    std::pair<size_t, size_t> _pos;
    Inventory _inv;
    size_t _level;
    size_t _orientation;
    std::string _team;
    size_t _id;
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::Clock _clock;
    bool _isIncantating = false;

    public:
    Player();
    Player(size_t x, size_t y, size_t id, std::string path);

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
    void setInventory(Stones stone, int quantity);

    size_t getId() const;
    void setId(size_t id);

    sf::Sprite *getSprite() const;
    void setSprite(std::string path);

    bool getIncantationStatus() const;
    void setIncantationStatus(bool value);

    void draw(sf::RenderWindow &window);

    void updateSpriteFrame();
};
