#include "Game.hpp"

void Game::inMainMenuLoop()
{

    UIButton startButton;
    startButton.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 100, 850));
    startButton.setSize(sf::Vector2f(200, 70));
    startButton.setText("Start");
    startButton.update(sf::Mouse::getPosition(window));

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

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left && startButton.isHovering())
                gameState = GameState::InSpace;
        }

    }

    float deltaTime = clock.restart().asSeconds();

    window.clear(sf::Color(30, 30, 160));

    std::string text = "Orbital Prospector";
    TextRenderer::drawText(window, {text, sf::Vector2f(WINDOW_WIDTH / 2, 150), sf::Color(255, 255, 255), 130, sf::Color(0, 0, 0), 4, true});

    startButton.draw(window);

    text = "Exit (ESC)";
    TextRenderer::drawText(window, {text, sf::Vector2f(20, 980), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3});

    window.display();

}