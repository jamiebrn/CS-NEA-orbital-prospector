#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Constants.hpp"
#include "PlayerShip.hpp"
#include "TextureManager.hpp"
#include "Camera.hpp"
#include "PlanetRenderer.hpp"
#include "TextRenderer.hpp"

int main()
{

    srand((unsigned)time(0));

    // Initialise

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close);

    sf::Image icon;
    if (!icon.loadFromFile(ICON_PATH))
    {
        std::cout << "ERROR: Cannot load window icon" << std::endl;
        return -1;
    }
    window.setIcon(icon.getSize(), icon.getPixelsPtr());

    if (!TextureManager::loadTextures())
    {
        std::cout << "ERROR: Textures have not been loaded correctly" << std::endl;
        return -1;
    }

    if (!TextRenderer::loadFont(FONT_PATH))
    {
        std::cout << "ERROR: Font has not been loaded correctly" << std::endl;
        return -1;
    }

    sf::Clock clock;

    PlanetRenderer mainPlanetRenderer(PlanetType::Earth);
    mainPlanetRenderer.setPosition(sf::Vector2f(1000, 1000));
    mainPlanetRenderer.setScale(6);

    PlayerShip playerShip;

    while (window.isOpen())
    {

        // Event handling
        
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }

        }

        // Logic

        float deltaTime = clock.restart().asSeconds();

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        playerShip.update(deltaTime, mousePosition);

        BulletManager::updateBullets(deltaTime);
        
        Camera::update(playerShip.getPosition(), deltaTime);

        mainPlanetRenderer.update(deltaTime);

        // Render

        window.clear();

        sf::Vector2f drawOffset = Camera::getDrawOffset();

        TextureDrawData backgroundData = {TextureType::EarthBackground, sf::Vector2f(drawOffset.x / 2, drawOffset.y / 2), sf::degrees(0), 3, false};
        TextureManager::drawSubTexture(window, backgroundData, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(WORLD_WIDTH, WORLD_HEIGHT)));

        mainPlanetRenderer.draw(window);

        BulletManager::drawBullets(window);

        playerShip.draw(window);

        // UI

        std::string fpsText = std::to_string(static_cast<int>(1 / deltaTime)) + " FPS";
        TextRenderer::drawText(window, {fpsText, sf::Vector2f(20, 10), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3});

        std::string bulletText = std::to_string(BulletManager::getBulletCount()) + " Bullets";
        TextRenderer::drawText(window, {bulletText, sf::Vector2f(20, 70), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3});

        window.display();

    }

    return 0;
}