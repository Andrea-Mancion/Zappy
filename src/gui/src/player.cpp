/*
** EPITECH PROJECT, 2023
** player.cpp
** File description:
** player
*/

#include "../inc/player.hpp"

Player::Player()
{
    _pos = std::pair<int, int>(0, 0);
    _inv = Inventory();
    _level = 1;
    _orientation = N;
    _team = "";
    _id = 0;
    _sprite = sf::Sprite();
}

Player::Player(size_t x, size_t y, size_t id, sf::Sprite sprite)
{
    _pos = std::pair<int, int>(x, y);
    _inv = Inventory();
    _level = 1;
    _orientation = N;
    _team = "";
    _id = id;
    _sprite = sprite;
}

Player::~Player()
{
}

std::pair<size_t, size_t> Player::getPos() const
{
    return _pos;
}

void Player::setPos(size_t x, size_t y)
{
    _pos.first = x;
    _pos.second = y;
}

void Player::setPos(std::pair<size_t, size_t> pos)
{
    _pos = pos;
}

size_t Player::getLevel() const
{
    return _level;
}

void Player::setLevel(size_t level)
{
    _level = level;
}

std::string Player::getTeam() const
{
    return _team;
}

void Player::setTeam(std::string name)
{
    _team = name;
}

Orientation_e Player::getOrientation() const
{
    return static_cast<Orientation_e>(_orientation);
}

void Player::setOrientation(size_t angle)
{
    _orientation = angle;
}

void Player::setOrientation(Orientation_e angle)
{
    _orientation = angle;
}

Inventory Player::getInventory() const
{
    return _inv;
}

void Player::setInventory(Inventory inv)
{
    _inv = inv;
}

size_t Player::getId() const
{
    return _id;
}

void Player::setId(size_t id)
{
    _id = id;
}

void Player::setSprite(sf::Sprite sprite)
{
    _sprite = sprite;
}

sf::Sprite Player::getSprite() const
{
    return _sprite;
}
