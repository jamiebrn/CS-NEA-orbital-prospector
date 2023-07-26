#include <SFML/Graphics.hpp>
#include <cmath>

#include "Constants.hpp"
#include "PlayerShip.hpp"

int main() {

    // Initialise

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), WINDOW_TITLE);
    sf::Clock clock;

    PlayerShip playerShip;

    while (window.isOpen()) {

        // Event handling
        
        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();

        }

        // Logic

        float deltaTime = clock.restart().asSeconds();

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        playerShip.update(deltaTime, mousePosition);

        // Render

        window.clear();

        playerShip.draw(window);

        window.display();

    }

    return 0;
}