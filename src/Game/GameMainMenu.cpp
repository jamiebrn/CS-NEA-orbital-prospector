// GameMainMenu.cpp

#include "Game.hpp"

// Game loop for main menu game state
void Game::inMainMenuLoop(float deltaTime)
{
    // Get mouse position
    sf::Vector2i screenMousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = window.mapPixelToCoords(screenMousePosition);

    // Create button for load data error popup
    UIButton loadDataErrorButton;

    // Set data of load data error button and update
    loadDataErrorButton.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 100, 600));
    loadDataErrorButton.setSize(sf::Vector2f(200, 70));
    loadDataErrorButton.setText("OK");
    loadDataErrorButton.setColour(sf::Color(190, 190, 190));
    loadDataErrorButton.setHoverColour(sf::Color(200, 200, 200));
    loadDataErrorButton.update(mousePosition);

    // If load data error popup is not present, update title buttons
    if (!loadDataError)
    {
        titleButtons.update(mousePosition);
    }

    // Iterate over all input events
    sf::Event event;
    while (window.pollEvent(event))
    {
        // If input event is window close, close window
        if (event.type == sf::Event::Closed)
            window.close();
        
        // If input event is mouse button pressed
        if (event.type == sf::Event::MouseButtonPressed)
        {
            // If load data error popup is active, check is load data error button is being pressed
            // If so, close load data error popup
            if (loadDataError)
            {
                if (loadDataError && event.mouseButton.button == sf::Mouse::Left && loadDataErrorButton.isHovering())
                    loadDataError = false;    
            }
            // If left mouse button is pressed, check if title buttons are pressed and calls respective functions if so
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

    // Update title planet animation
    titlePlanetRenderer.update(deltaTime);

    // Clear window
    window.clear();

    // Draw space background using randomise area
    TextureDrawData backgroundData = {TextureType::EarthBackground, sf::Vector2f(0, 0), sf::degrees(0), 3, false};
    TextureManager::drawSubTexture(window, backgroundData, sf::IntRect(titleBackgroundSubRectPos, sf::Vector2i(WINDOW_WIDTH, WINDOW_HEIGHT)));

    // Draw title planet
    titlePlanetRenderer.draw(window, false);

    // Draw game title
    std::string text = "Orbital Prospector";
    TextRenderer::drawText(window, {text, sf::Vector2f(WINDOW_WIDTH / 2, 150), sf::Color(255, 255, 255), 130, sf::Color(0, 0, 0), 4, true});

    // Draw menu/title buttons
    titleButtons.draw(window);

    // If load data error, draw load data popup
    if (loadDataError)
    {
        // Draw popup background
        sf::RectangleShape background(sf::Vector2f(600, 400));
        background.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 300, WINDOW_HEIGHT / 2 - 200));
        background.setFillColor(sf::Color(20, 20, 20, 160));
        window.draw(background);

        // Set error message based on error type
        std::string errorMessage;
        if (loadDataErrorType == LoadDataSuccess::NO_FILE)
            errorMessage = "No save file found";
        else
            errorMessage = "Save file is corrupt";

        // Draw error message text
        TextRenderer::drawText(window, {
            errorMessage, sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
            sf::Color(255, 255, 255), 40,
            sf::Color(0, 0, 0), 3,
            true, true
        });

        // Draw load data error button
        loadDataErrorButton.draw(window);
    }

}

// Start a new game
void Game::newGame()
{
    // Reset game variables
    resetGame();

    // Reset player ship stats
    playerShip.setPosition(sf::Vector2f(5000, 5000));
    playerShip.setHealth(STARTING_MAX_HEALTH);
    playerShip.setMaxHealth(STARTING_MAX_HEALTH);

    // Reset camera position
    Camera::setOffset(sf::Vector2f(4500, 4000));

    // Set planet to earth
    currentPlanet = PlanetType::Earth;
    mainPlanetRenderer.setPlanetType(currentPlanet);

    // Generate asteroids
    for (int i = 0; i < ASTEROID_MAX; i++)
    {
        sf::Vector2f position(rand() % static_cast<int>(WORLD_WIDTH), rand() % static_cast<int>(WORLD_HEIGHT));
        AsteroidManager::createAsteroid(position);
    }
    
    // Sort asteroids, as just generated
    AsteroidManager::sortAsteroids();

    // Regenerate all missions
    MissionManager::rerollAllMissions();

    // Transition to in space game state
    targetGameState = GameState::InSpace;
}

// Load game, by loading save data
void Game::loadGame()
{
    // Reset game variables
    resetGame();

    // Load game data, getting success
    LoadDataSuccess loadSuccess = loadData();

    // If load wasn't success, store error type
    if (loadSuccess != LoadDataSuccess::SUCCESSFUL)
    {
        loadDataError = true;
        loadDataErrorType = loadSuccess;
        return;
    }

    // Transition to in space station if loaded successfully
    targetGameState = GameState::InSpace;
}

// Reset game variables, such as asteroids, enemies, and bullets
void Game::resetGame()
{
    // Set values to default
    paused = false;
    showUIRing = true;

    // Clear all managers
    AsteroidManager::reset();
    BulletManager::reset();
    ItemPickupManager::reset();
    EnemyShipManager::reset();
    InventoryManager::reset();
    UpgradeManager::reset();

    // Set planet to earth
    currentPlanet = PlanetType::Earth;

    // Reset level bar
    levelBar.reset();
    levelBar.setMaxValue(InventoryManager::getMaxLevelExp());
}