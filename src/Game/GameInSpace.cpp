// GameInSpace.cpp

#include "Game.hpp"

// Game loop for in space game state
void Game::inSpaceLoop(float deltaTime)
{

    // Get mouse position
    sf::Vector2i screenMousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = window.mapPixelToCoords(screenMousePosition);


    // Event handling

    // Variable storing whether left mouse button was pressed, default to false
    bool leftMousePressed = false;

    // Iterate over all input events
    sf::Event event;
    while (window.pollEvent(event))
    {

        // If input event is close window, close the window
        if (event.type == sf::Event::Closed)
            window.close();
        
        // If input event is key press, detect for different key presses
        if (event.type == sf::Event::KeyPressed)
        {
            // If key press is escape key, toggle pause menu
            if (event.key.code == sf::Keyboard::Escape)
            {
                paused = !paused;
                pauseMenuButtons.setButtonText("save", "Save");
            }

            // If key press is E key
            if (event.key.code == sf::Keyboard::E)
            {
                // If if space station range, transition to in space station state
                if (inStationRange)
                    targetGameState = GameState::InStation;
            }

            // If key press is H key, toggle UI ring
            if (event.key.code == sf::Keyboard::H)
                showUIRing = !showUIRing;
            
            /* Add enemy ship while testing

            if (event.key.code == sf::Keyboard::G)
            {
                sf::Vector2f pos = mousePosition - Camera::getDrawOffset();
                EnemyShipManager::addShip(EnemyShip(pos));
            }
            */

        }

        // If left mouse button is pressed, set left mouse pressed variable to true
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
                leftMousePressed = true;
        }

    }

    // If in pause menu and left mouse button pressed, test buttons
    if (paused && leftMousePressed)
    {
        // If resume button pressed, set pause to false
        if (pauseMenuButtons.isButtonPressed("resume"))
        {
            paused = false;
        }
        // If save button is pressed, save data
        else if (pauseMenuButtons.isButtonPressed("save"))
        {
            // Save data
            saveData();
            // Set save button text to "Saved!"
            pauseMenuButtons.setButtonText("save", "Saved!");
        }
        // If quit button is pressed, transition to main menu state
        else if (pauseMenuButtons.isButtonPressed("quit"))
        {
            targetGameState = GameState::MainMenu;
        }
    }
    

    // Game loop logic
    
    // Get camera draw offset
    sf::Vector2f drawOffset = Camera::getDrawOffset();

    // If game is not paused, update as normal
    if (!paused)
    {
        // Update player ship
        playerShip.update(deltaTime, mousePosition);

        // Update all enemy ships with enemy ship manager
        EnemyShipManager::updateShips(playerShip, deltaTime);

        // Update all player ship bullets in bullet manager
        BulletManager::updateBullets(deltaTime);
        // Update all enemy ship bullets in bullet manager
        BulletManager::updateEnemyBullets(deltaTime);

        // Update all asteroids in asteroid manager
        AsteroidManager::updateAsteroids(currentPlanet, deltaTime);

        // Calculate position of centre of planet for space station to orbit
        float unprojectMult = Helper::unprojectDepthMultiplier(PLANET_DEPTH_DIVIDE, SPACE_STATION_DEPTH_DIVIDE);
        sf::Vector2f planetCentre = mainPlanetRenderer.getPosition();
        planetCentre += drawOffset * unprojectMult;

        // Update space station orbit around calculated planet centre
        spaceStation.orbitBody(planetCentre, 1400, 1, deltaTime);

        // Update whether player ship is in space station range
        inStationRange = (distanceSqToStation() <= STATION_MAX_RANGE * STATION_MAX_RANGE);

        // Update main planet renderer animation
        mainPlanetRenderer.update(deltaTime);

        // Calculate space station position normalised to standard depth
        unprojectMult = Helper::unprojectDepthMultiplier(SPACE_STATION_DEPTH_DIVIDE, 1);
        sf::Vector2f spaceStationPos = spaceStation.getPosition() + drawOffset * unprojectMult;

        // Update UI navigation ring with space station position and enemy ship positions
        UIRingManager::update(spaceStationPos, EnemyShipManager::getShips());

        // Update player health bar with data
        playerHealthBar.setMaxValue(UpgradeManager::getHealthAmount());
        playerHealthBar.setWidth(UpgradeManager::getHealthAmount() * 9);
        playerHealthBar.updateValue(playerShip.getHealth());
        playerHealthBar.update(deltaTime);

        // Update level bar with data
        levelBar.setMaxValue(InventoryManager::getMaxLevelExp());
        levelBar.updateValue(InventoryManager::getLevelExp());
        levelBar.update(deltaTime);

        // Update camera with player ship position
        Camera::update(playerShip.getPosition(), deltaTime);
    }
    // If paused, update pause menu buttons
    else
    {
        pauseMenuButtons.update(mousePosition);
    }


    // Render

    // Clear window
    window.clear();

    // Draw space background
    TextureDrawData backgroundData = {TextureType::EarthBackground, drawOffset / BACKGROUND_DEPTH_DIVIDE, sf::degrees(0), 3, false};
    TextureManager::drawSubTexture(window, backgroundData, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(WORLD_WIDTH, WORLD_HEIGHT)));

    // Draw planet
    mainPlanetRenderer.draw(window);

    // Draw space station
    spaceStation.draw(window);

    // Draw all asteroids
    AsteroidManager::drawAsteroids(window);

    // Draw all item pickups
    ItemPickupManager::drawPickups(window);

    // Draw all player ship bullets
    BulletManager::drawBullets(window);
    // Draw all enemy ship bullets
    BulletManager::drawEnemyBullets(window);

    // Draw all enemy ships
    EnemyShipManager::drawShips(window);

    // Draw player ship
    playerShip.draw(window);

    // UI

    // If player ship is alive, draw UI elements
    if (playerShip.isAlive())
    {

        // Draw player health bar
        playerHealthBar.draw(window);

        // Draw text on player health bar, showing remaining health
        std::string text = std::to_string(static_cast<int>(playerShip.getHealth())) + " / " + std::to_string(UpgradeManager::getHealthAmount()) + " HP";
        TextRenderer::drawText(window, {
            text, sf::Vector2f(50, 55),
            sf::Color(255, 255, 255), 32, sf::Color(0, 0, 0), 3,
            false, true
        });

        // Draw player level bar
        levelBar.draw(window);

        // Draw text on level bar, showing level progress
        text = ("Level " + std::to_string(InventoryManager::getCurrentLevel())
            + " - " + std::to_string(static_cast<int>(levelBar.getValue())) + " / " + 
            std::to_string(static_cast<int>(levelBar.getMaxValue())) + " XP");
            
        TextRenderer::drawText(window, {
            text, sf::Vector2f(WINDOW_WIDTH / 2, 55),
            sf::Color(255, 255, 255), 32, sf::Color(0, 0, 0), 3,
            true, true
        });

        // If in space station range, draw enter station prompt
        if (inStationRange)
        {
            text = "Enter Station (E)";
            TextRenderer::drawText(window, {
                text, sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 * 3),
                sf::Color(255, 255, 255), 50, sf::Color(0, 0, 0), 3, true
            });
        }

        // If show UI ring, draw UI navigation ring
        if (showUIRing)
            UIRingManager::draw(window);
        
        // If mission is currently in progress, draw mission progress UI elements
        if (MissionManager::hasAcceptedMission())
            drawMissionProgress(deltaTime);
        
    }
    // If player ship is not alive, draw "You died" text
    else
    {
        std::string text = "You died";
        TextRenderer::drawText(window, {
            text, sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
            sf::Color(255, 255, 255), 72, sf::Color(0, 0, 0), 4,
            true, true
        });
    }
    

    // If paused, draw pause menu
    if (paused)
    {
        // Draw pause background
        sf::RectangleShape background(sf::Vector2f(300, 400));
        background.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 200));
        background.setFillColor(sf::Color(20, 20, 20, 150));

        window.draw(background);

        // Draw pause menu buttons
        pauseMenuButtons.draw(window);
    }

}

// Draw mission progress UI element
void Game::drawMissionProgress(float deltaTime)
{
    // Draw border/background
    sf::RectangleShape missionBorder(sf::Vector2f(370, 80));
    missionBorder.setPosition(sf::Vector2f(1550, 165));
    missionBorder.setFillColor(sf::Color(30, 30, 30, 120));
    window.draw(missionBorder);

    // Draw accent colour strip
    sf::RectangleShape missionBorderColor(sf::Vector2f(10, 80));
    missionBorderColor.setPosition(sf::Vector2f(1550, 165));
    missionBorderColor.setFillColor(sf::Color(24, 176, 231, 200));
    window.draw(missionBorderColor);

    // Get current mission data
    int missionId = MissionManager::getAcceptedMissionId();
    const Mission& mission = MissionManager::getMissionData(missionId);

    // Get mission goal progress
    int goalProgress = MissionManager::getGoalProgress();

    // Draw mission title
    TextRenderer::drawText(window, {
        mission.title, sf::Vector2f(1735, 185),
        sf::Color(255, 255, 255), 32, sf::Color(0, 0, 0), 3, true, true
    });

    // If mission is not completed, draw mission progress bar
    if (!MissionManager::missionCompleted())
    {
        // Update mission progress bar
        missionProgress.setMaxValue(mission.goalAmount);
        missionProgress.updateValue(goalProgress);
        missionProgress.update(deltaTime);

        // Draw mission progress bar
        missionProgress.draw(window);

        // Draw mission progress text
        TextRenderer::drawText(window, {
            std::to_string(goalProgress) + " / " + std::to_string(mission.goalAmount),
            sf::Vector2f(1735, 223), sf::Color(255, 255, 255), 32, sf::Color(0, 0, 0),
            3, true, true
        });
    }
    // If mission is completed, draw "completed" text
    else
    {
        TextRenderer::drawText(window, {
            "Completed!", sf::Vector2f(1735, 223), sf::Color(255, 255, 255),
            32, sf::Color(0, 0, 0), 3, true, true
        });
    }

}

// Calculate square distance between player ship and space station
float Game::distanceSqToStation()
{
    // Get draw offset
    sf::Vector2f drawOffset = Camera::getDrawOffset();

    // Get space station position and convert to standard depth
    float unprojStation = Helper::unprojectDepthMultiplier(SPACE_STATION_DEPTH_DIVIDE, 1);
    sf::Vector2f stationPos = spaceStation.getPosition();
    stationPos += drawOffset * unprojStation;

    // Calculate square distance
    float distanceSq = (playerShip.getPosition() - stationPos).lengthSq();

    // Return calculated square distance
    return distanceSq;
}

// Changes current planet and resets necessary variables
void Game::travelToPlanet(PlanetType planet)
{
    // Set current planet to new planet
    currentPlanet = planet;

    // Set planet renderer type
    mainPlanetRenderer.setPlanetType(currentPlanet);

    // Reset player ship position and camera offset
    playerShip.setPosition(sf::Vector2f(5000, 5000));
    Camera::setOffset(sf::Vector2f(5000, 5000));

    // Randomise space station orbit angle
    spaceStation.setOrbitAngle(rand() % 360);

    // Reset managers
    AsteroidManager::reset();
    BulletManager::reset();
    ItemPickupManager::reset();
    EnemyShipManager::reset();

    // Generate asteroids
    for (int i = 0; i < ASTEROID_MAX; i++)
    {
        sf::Vector2f position(rand() % static_cast<int>(WORLD_WIDTH), rand() % static_cast<int>(WORLD_HEIGHT));
        AsteroidManager::createAsteroid(position);
    }

    // Resort all asteroids
    AsteroidManager::sortAsteroids();

    // Set travel time timer
    travelTime = TRAVEL_TIME;

    // Transition to travelling game state
    targetGameState = GameState::Travelling;
}
