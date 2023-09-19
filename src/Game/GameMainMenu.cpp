#include "Game.hpp"

void Game::inMainMenuLoop()
{

    sf::Vector2i screenMousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = window.mapPixelToCoords(screenMousePosition);

    UIButton loadDataErrorButton;
    loadDataErrorButton.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 100, 600));
    loadDataErrorButton.setSize(sf::Vector2f(200, 70));
    loadDataErrorButton.setText("OK");
    loadDataErrorButton.setColour(sf::Color(190, 190, 190));
    loadDataErrorButton.setHoverColour(sf::Color(200, 200, 200));
    loadDataErrorButton.update(mousePosition);

    if (!loadDataError)
    {
        titleButtons.update(mousePosition);
    }

    sf::Event event;
    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed)
        {   
            if (loadDataError)
            {
                if (loadDataError && event.mouseButton.button == sf::Mouse::Left && loadDataErrorButton.isHovering())
                    loadDataError = false;    
            }
            else if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (titleButtons.isButtonPressed("new"))
                {
                    newGame();
                }
                if (titleButtons.isButtonPressed("load"))
                {
                    loadGame();
                }
                if (titleButtons.isButtonPressed("quit"))
                {
                    window.close();
                }
            }

        }

    }

    float deltaTime = clock.restart().asSeconds();
    
    titlePlanetRenderer.update(deltaTime);

    window.clear(sf::Color(15, 15, 130));

    TextureDrawData backgroundData = {TextureType::EarthBackground, sf::Vector2f(0, 0), sf::degrees(0), 3, false};
    TextureManager::drawSubTexture(window, backgroundData, sf::IntRect(titleBackgroundSubRectPos, sf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)));

    titlePlanetRenderer.draw(window);

    std::string text = "Orbital Prospector";
    TextRenderer::drawText(window, {text, sf::Vector2f(WINDOW_WIDTH / 2, 150), sf::Color(255, 255, 255), 130, sf::Color(0, 0, 0), 4, true});

    titleButtons.draw(window);

    if (loadDataError)
    {

        sf::RectangleShape background(sf::Vector2f(600, 400));
        background.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT / 2 - 200));
        background.setFillColor(sf::Color(20, 20, 20, 160));
        window.draw(background);

        std::string errorMessage = "None";
        if (loadDataErrorType == LoadDataSuccess::NO_FILE)
        {
            errorMessage = "No save file found";
        }
        else
        {
            errorMessage = "Save file is corrupt";
        }

        TextRenderer::drawText(window, {
            errorMessage, sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
            sf::Color(255, 255, 255), 40,
            sf::Color(0, 0, 0), 3,
            true, true
        });

        loadDataErrorButton.draw(window);

    }

    window.display();

}

void Game::newGame()
{

    resetGame();

    InventoryManager::resetSilverCoins();
    playerShip.setPosition(sf::Vector2f(5000, 5000));
    Camera::setOffset(sf::Vector2f(4500, 4000));

    for (int i = 0; i < ASTEROID_MAX; i++)
    {
        sf::Vector2f position(rand() % static_cast<int>(WORLD_WIDTH), rand() % static_cast<int>(WORLD_HEIGHT));
        AsteroidManager::createAsteroid(position);
    }

    changeState(GameState::InSpace);

}

void Game::loadGame()
{

    resetGame();

    LoadDataSuccess loadSuccess = loadData();

    if (loadSuccess != LoadDataSuccess::SUCCESSFUL)
    {
        loadDataError = true;
        loadDataErrorType = loadSuccess;
        return;
    }

    changeState(GameState::InSpace);

}

void Game::resetGame()
{

    paused = false;
    showUIRing = true;

    AsteroidManager::reset();
    BulletManager::reset();
    ItemPickupManager::reset();
    EnemyShipManager::reset();
    InventoryManager::reset();

    levelBar.reset();
    levelBar.setMaxValue(InventoryManager::getMaxLevelExp());

    EnemyShipManager::addShip(sf::Vector2f(5000, 4500));

}