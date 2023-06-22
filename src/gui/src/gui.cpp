/*
** EPITECH PROJECT, 2023
** hui.cpp
** File description:
** main function
*/

#include "../inc/gui.hpp"

int main(int ac, char **av)
{
    sf::RenderWindow window(sf::VideoMode(1580, 920), "Zappy GUI");

    Server *server;
    Map map(0, 0, "assets/grass1.png", &window);
    Commands cmd;

    try {
        server = new Server(ac, av);
    } catch (ServerError &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }
    while (window.isOpen()) {
        sf::Event event;
        if (server->isReceivingTransmission())
            cmd.doCommand(&map, server->getTransmission(), *server);
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::Closed)
                window.close();
        }
        map.draw_map(window);
        map.draw_players(window);
        window.display();
        map.inventoryDisplay(window);
    }
    return 0;
}
