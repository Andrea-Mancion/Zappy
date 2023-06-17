/*
** EPITECH PROJECT, 2023
** map.cpp
** File description:
** window and map
*/

#include "../inc/gui.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1580, 920), "SFML works!");

    sf::Sprite sprite = createSprite("assets/grass1.png", 0.5f);
    sf::Sprite playerSprite = createSprite("assets/player/dino.png", 0.3f);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Resized)
            {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

            draw_map(window, sprite, playerSprite);

            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    return 0;
}
