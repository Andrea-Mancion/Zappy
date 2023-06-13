/*
** EPITECH PROJECT, 2023
** map.cpp
** File description:
** window and map
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include "inc/map.hpp"

void map(sf::RenderWindow *window, sf::Sprite sprite)
{
    sf::Vector2u size = window->getSize();
    sf::FloatRect bounds = sprite.getGlobalBounds();

    window->clear();

    for (size_t i = 0; i < MAP_RANGE; i++) 
    {
        for (size_t j = 0; j < MAP_RANGE; j++)
        {
            float isoX = (i - j) * 0.5f * (bounds.width / 2) + size.x / 2;
            float isoY = (i + j) * 0.5f * (bounds.height / 2) + size.y / 4;

            sprite.setPosition((int)isoX, (int)isoY);
            window->draw(sprite);
        }
    }
    window->display();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1080, 720), "SFML works!");

    sf::Texture texture;
    if (!texture.loadFromFile("assets/grass1.png")) {
        return 1;
    }
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f);

    unsigned int width = 0;
    unsigned int height = 0;


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Resized) {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

            map(&window, sprite);

            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    return 0;
}

