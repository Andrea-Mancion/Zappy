/*
** EPITECH PROJECT, 2023
** map.cpp
** File description:
** window and map
*/

#include "../inc/gui.hpp"

int main(int ac, char **av)
{
    sf::RenderWindow window(sf::VideoMode(1580, 920), "SFML works!");

    sf::Sprite sprite = createSprite("assets/grass1.png", 0.5f);
    sf::Sprite playerSprite = createSprite("assets/player/dino.png", 0.3f);
    Server *server;
    Map map;

    try {
        server = new Server(ac, av);
    } catch (ServerError &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
    while (window.isOpen()) {
        sf::Event event;
        if (server->isReceivingTransmission())
            server->getTransmission();
        while (window.pollEvent(event)) {
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
