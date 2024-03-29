/*
** EPITECH PROJECT, 2023
** gui.cpp
** File description:
** main function
*/

#include <SFML/Graphics.hpp>

#include "../inc/gui.hpp"

void configureSquare(sf::RectangleShape &square, float zoomLevel)
{
    square.setSize(sf::Vector2f(400 * zoomLevel, 400 * zoomLevel));
    square.setFillColor(sf::Color(0, 0, 0, 128));
}

void updateCloud(sf::Sprite &cloudSprite, float &cloudX, float cloudSpeed, float deltaTime, const sf::Vector2u &windowSize)
{
    cloudX -= cloudSpeed * deltaTime;

    if (cloudX < -cloudSprite.getGlobalBounds().width)
        cloudX = windowSize.x;

    cloudSprite.setPosition(cloudX, cloudSprite.getPosition().y);
}

int main(int ac, char **av)
{
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Zappy GUI");

    sf::RectangleShape square;
    float zoomLevel = 1.0f;
    configureSquare(square, zoomLevel);

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::Vector2u desktopSize(desktopMode.width, desktopMode.height);
    sf::Vector2f squarePosition(desktopSize.x - square.getSize().x, desktopSize.y - square.getSize().y);
    square.setPosition(squarePosition);

    Server *server;
    Map map(0, 0, "assets/grass.png", &window);
    Commands cmd;
    sf::Mouse mouse;
    bool pressed = false;

    try {
        server = new Server(ac, av);
    }
    catch (ServerError &e) {
        std::cout << e.what() << std::endl;
        return 84;
    }

    sf::Texture cloudTexture1;
    if (cloudTexture1.loadFromFile("assets/cloud.png")) {
        sf::Sprite cloudSprite1(cloudTexture1);
        float scale = 0.5f;
        cloudSprite1.setScale(scale * zoomLevel, scale * zoomLevel);
        float cloudX1 = window.getSize().x;
        float cloudY1 = 100.0f;
        cloudSprite1.setPosition(cloudX1, cloudY1);

        sf::Texture cloudTexture2;
        if (cloudTexture2.loadFromFile("assets/cloud2.png")) {
            sf::Sprite cloudSprite2(cloudTexture2);
            cloudSprite2.setScale(scale * zoomLevel, scale * zoomLevel);
            float cloudX2 = window.getSize().x / 2.0f;
            float cloudY2 = 200.0f;
            cloudSprite2.setPosition(cloudX2, cloudY2);

            sf::Clock clock;
            float cloudSpeed = 100.0f;

            while (window.isOpen()) {
                sf::Event event;
                sf::View view = window.getView();
                if (server->isReceivingTransmission())
                    cmd.doCommand(&map, server->getTransmission(), *server);
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Resized) {
                        sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                        window.setView(sf::View(visibleArea));
                    } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                        map.setDisplayInventory(false);
                    } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down && !pressed) {
                        pressed = true;
                        if (map.getZoom() > (float)5.0)
                            map.setZoom(5);
                        view.zoom(1.1);
                        window.setView(view);
                        map.setZoom(view.getSize().x / float(1920));
                    } else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up && !pressed) {
                        pressed = true;
                        if (map.getZoom() < (float)0.5)
                            map.setZoom(0.5);
                        view.zoom(0.9);
                        window.setView(view);
                        map.setZoom(view.getSize().x / float(1920));
                    } else if (event.type == sf::Event::KeyReleased && pressed) {
                        pressed = false;
                    } else if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    map.setDisplayInventory(false);
                }
                square.setPosition(window.mapPixelToCoords(sf::Vector2i(squarePosition)));
                square.setScale(400 * map.getZoom(), 400 * map.getZoom());
                sf::Time elapsed = clock.restart();
                float deltaTime = elapsed.asSeconds();

                updateCloud(cloudSprite1, cloudX1, cloudSpeed, deltaTime, window.getSize());
                updateCloud(cloudSprite2, cloudX2, cloudSpeed * 0.8f, deltaTime, window.getSize());

                sf::Color backgroundColor(176, 224, 230);
                window.clear(backgroundColor);

                window.draw(cloudSprite1);
                window.draw(cloudSprite2);
                map.drawMap(window, zoomLevel);
                map.drawResources(window);
                map.draw_players(window);
                map.inventoryDisplay(window);
                map.drawLeaderboard(window);
                window.draw(square);
                map.drawBroadcast(window);
                window.display();
            }
        }
    }
    return 0;
}
