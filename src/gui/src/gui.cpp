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
    sf::Mouse mouse;

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
            } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                    map.setDisplayInventory(false);
                    break;
            } else if (event.type == sf::Event::Closed)
                window.close();
        }
        if (mouse.isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i pos = mouse.getPosition(window);
            printf("MOUSE POS: %d %d\n", pos.x, pos.y);
            for (size_t i = 0; i < map.getPlayers()->size(); i++) {
                if (map.getPlayer(i)->getSprite()->getGlobalBounds().contains(pos.x, pos.y)) {
                    printf("TRIGGER\n");
                    map.setDisplayInventory(true, map.getPlayer(i)->getId());
                    break;
                }
            }
        }
        map.draw_map(window);
        map.draw_players(window);
        map.inventoryDisplay(window);
        window.display();
    }
    return 0;
}
