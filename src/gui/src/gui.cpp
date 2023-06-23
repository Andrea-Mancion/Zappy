/*
** EPITECH PROJECT, 2023
** hui.cpp
** File description:
** main function
*/

#include "../inc/gui.hpp"

void updateCloud(sf::Sprite& cloudSprite, float& cloudX, float cloudSpeed, float deltaTime, const sf::Vector2u& windowSize)
{
    cloudX -= cloudSpeed * deltaTime;

    if (cloudX < -cloudSprite.getGlobalBounds().width)
        cloudX = windowSize.x;

    cloudSprite.setPosition(cloudX, cloudSprite.getPosition().y);
}

int main(int ac, char **av)
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktopMode, "Zappy GUI");

    Server *server;
    Map map(0, 0, "assets/grass7.png", &window);
    Commands cmd;
    sf::Mouse mouse;

    try {
        server = new Server(ac, av);
    }
    catch (ServerError &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }

    float zoomLevel = 1.0f;

    sf::Texture cloudTexture1;
    if (cloudTexture1.loadFromFile("assets/cloud.png")) {
        sf::Sprite cloudSprite1(cloudTexture1);
        float scale = 0.5f;
        cloudSprite1.setScale(scale, scale);
        float cloudX1 = window.getSize().x;
        float cloudY1 = 100.0f;
        cloudSprite1.setPosition(cloudX1, cloudY1);

        sf::Texture cloudTexture2;
        if (cloudTexture2.loadFromFile("assets/cloud2.png")) {
            sf::Sprite cloudSprite2(cloudTexture2);
            cloudSprite2.setScale(scale, scale);
            float cloudX2 = window.getSize().x / 2.0f;
            float cloudY2 = 200.0f;
            cloudSprite2.setPosition(cloudX2, cloudY2);

            sf::Clock clock;
            float cloudSpeed = 100.0f;

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
                    } else if (event.type == sf::Event::MouseWheelScrolled) {
                        if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                            zoomLevel *= (event.mouseWheelScroll.delta > 0) ? 1.1f : 0.9f;
                            if (zoomLevel < 0.2f)
                                zoomLevel = 0.2f;
                            if (zoomLevel > 5.0f)
                                zoomLevel = 5.0f;
                        }
                    } else if (event.type == sf::Event::Closed) {
                        window.close();
                    }
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
                sf::Time elapsed = clock.restart();
                float deltaTime = elapsed.asSeconds();

                updateCloud(cloudSprite1, cloudX1, cloudSpeed, deltaTime, window.getSize());
                updateCloud(cloudSprite2, cloudX2, cloudSpeed * 0.8f, deltaTime, window.getSize());

                window.clear();
                map.draw_map(window, zoomLevel);
                map.draw_players(window);
                map.inventoryDisplay(window);
                window.draw(cloudSprite1);
                window.draw(cloudSprite2);
                window.display();
            }
        }
    }
    return 0;
}
