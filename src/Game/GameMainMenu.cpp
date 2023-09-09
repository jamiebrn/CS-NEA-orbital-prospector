#include "Game.hpp"

void Game::inMainMenuLoop()
{

    UIButton newButton;
    newButton.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 100, 700));
    newButton.setSize(sf::Vector2f(200, 70));
    newButton.setText("New");
    newButton.setColour(sf::Color(15, 190, 15));
    newButton.setHoverColour(sf::Color(20, 220, 20));
    newButton.update(sf::Mouse::getPosition(window));

    UIButton loadButton;
    loadButton.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 100, 800));
    loadButton.setSize(sf::Vector2f(200, 70));
    loadButton.setText("Load");
    loadButton.setColour(sf::Color(15, 15, 190));
    loadButton.setHoverColour(sf::Color(20, 20, 220));
    loadButton.update(sf::Mouse::getPosition(window));

    UIButton quitButton;
    quitButton.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 100, 900));
    quitButton.setSize(sf::Vector2f(200, 70));
    quitButton.setText("Quit");
    quitButton.setColour(sf::Color(190, 15, 15));
    quitButton.setHoverColour(sf::Color(220, 20, 20));
    quitButton.update(sf::Mouse::getPosition(window));

    sf::Event event;
    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left && newButton.isHovering())
            {
                newGame();
            }
            if (event.mouseButton.button == sf::Mouse::Left && loadButton.isHovering())
            {
                loadGame();
            }
            if (event.mouseButton.button == sf::Mouse::Left && quitButton.isHovering())
            {
                window.close();
            }
        }

    }

    float deltaTime = clock.restart().asSeconds();

    window.clear(sf::Color(15, 15, 130));

    std::string text = "Orbital Prospector";
    TextRenderer::drawText(window, {text, sf::Vector2f(WINDOW_WIDTH / 2, 150), sf::Color(255, 255, 255), 130, sf::Color(0, 0, 0), 4, true});

    newButton.draw(window);
    loadButton.draw(window);
    quitButton.draw(window);

    window.display();

}

void Game::newGame()
{

    paused = false;
    AsteroidManager::empty();
    BulletManager::empty();

    InventoryManager::resetSilverCoins();
    playerShip.setPosition(sf::Vector2f(5000, 5000));
    Camera::setOffset(sf::Vector2f(4500, 4000));

    for (int i = 0; i < 1000; i++)
    {
        sf::Vector2f position(rand() % static_cast<int>(WORLD_WIDTH), rand() % static_cast<int>(WORLD_HEIGHT));
        AsteroidManager::createAsteroid(position);
    }

    changeState(GameState::InSpace);

}

void Game::loadGame()
{

    paused = false;
    AsteroidManager::empty();
    BulletManager::empty();

    if (!loadData())
        newGame();

    changeState(GameState::InSpace);

}