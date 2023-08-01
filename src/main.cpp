#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Constants.hpp"
#include "PlayerShip.hpp"
#include "TextureManager.hpp"

int main()
{

    // Initialise

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), WINDOW_TITLE, sf::Style::Close);

    sf::Image icon;
    if (!icon.loadFromFile(ICON_PATH))
    {
        std::cout << "ERROR: Cannot load window icon" << std::endl;
        return -1;
    }
    window.setIcon(icon.getSize(), icon.getPixelsPtr());

    sf::Clock clock;

    if (!TextureManager::loadTextures())
    {
        std::cout << "ERROR: Textures have not been loaded correctly" << std::endl;
        return -1;
    }

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

        window.setTitle(WINDOW_TITLE + std::string(" - ") + std::to_string(static_cast<int>(1 / deltaTime)) + " FPS");

        // Render

        window.clear();

        TextureManager::drawSubTexture(window, TextureType::EarthBackground, sf::Vector2f(0, 0), 1, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(1280, 720)));

        playerShip.draw(window);

        window.display();

    }

    return 0;
}