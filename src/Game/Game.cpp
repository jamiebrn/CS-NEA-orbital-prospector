// Game.cpp

#include "Game.hpp"

// Game loop, where the actual game runs
void Game::mainLoop()
{

    // While the game window is open, carry out game logic
    while (window.isOpen())
    {
        // Get delta time for use in game logic calculations
        float deltaTime = clock.restart().asSeconds();

        // Switch which game loop function is called based on current game state
        switch (gameState)
        {
        
        // Call main menu game loop when in main menu state
		case GameState::MainMenu:
			inMainMenuLoop(deltaTime);
			break;
		
        // Call in space game loop when in space state
		case GameState::InSpace:
			inSpaceLoop(deltaTime);
			break;
		
        // Call in station game loop when in station state
		case GameState::InStation:
			inStationLoop(deltaTime);
			break;
        
        // Call travelling game loop when in travelling state
        case GameState::Travelling:
            travellingLoop(deltaTime);
            break;

        }

        // Update and draw game state fade transition (only draws if transitioning)
        drawGameStateTransition(deltaTime);

        // Update window with new data
        window.display();

    }

}

// Change game state
void Game::changeState(GameState newState)
{
    // If state is being changed to space station state, ensure that space station
    // UI state is reset to main UI state
    if (newState == GameState::InStation)
    {
        stationMenuState = StationMenuState::Main;
    }
    // If state is being changed to main menu, reset camera position and play menu music
    else if (newState == GameState::MainMenu)
    {
        Camera::setOffset(sf::Vector2f(0, 0));
        SoundManager::playMusic(MusicType::Menu);
    }
    // If state is being changed to in space state from main menu state, play main game music
    else if (newState == GameState::InSpace && gameState == GameState::MainMenu)
    {
        SoundManager::playMusic(MusicType::Track1);
    }

    // Set game state to new state
    gameState = newState;
}

// Draw fade transition for transitioning between game states
void Game::drawGameStateTransition(float deltaTime)
{
    // Create rectangle covering whole screen for fade effect
    sf::RectangleShape fadeRect(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

    // Set position and colour of rectangle, with alpha of rectangle depending on the state transition timer
    fadeRect.setPosition(sf::Vector2f(0, 0));
    fadeRect.setFillColor(sf::Color(0, 0, 0, (gameStateTransitionTimer / GAME_STATE_TRANSITION_TIME) * 255));

    // If transition timer is active, draw rectangle to create fade effect
    if (gameStateTransitionTimer > 0)
        window.draw(fadeRect);
    
    // If transitioning to a new state, build up the timer to max time
    if (targetGameState != gameState)
    {
        // Add to timer
        gameStateTransitionTimer += deltaTime;

        // If timer has reached max time, switch game state to target game state
        if (gameStateTransitionTimer >= GAME_STATE_TRANSITION_TIME)
        {
            changeState(targetGameState);
        }

        // Return to prevent subtracting from timer
        return;
    }

    // Subtract from timer if not transitioning to new state to give fade out effect
    gameStateTransitionTimer = std::max(gameStateTransitionTimer - deltaTime, 0.0f);

}

// Load save data
LoadDataSuccess Game::loadData()
{
    // Attempt to open save file in binary format
    std::ifstream file("save.data", std::ios::binary);

    // If cannot find save file, return no file found error
    if (file.fail())
        return LoadDataSuccess::NO_FILE;
    
    // Attempt to load data from file
    try
    {
        // Create json object from save file data
        nlohmann::json saveData = nlohmann::json::from_bson(file);

        // Load all inventory items from save data file
        for (auto itemPair : itemTextureMap)
        {
            ItemPickupType type = itemPair.first;
            InventoryManager::addItem(type, saveData.at("inventory").at(magic_enum::enum_name(type)));
        }

        // Get all player upgrades from the save data file and unlock them
        std::vector<std::string> currentUpgrades = saveData.at("upgrades");
        for (std::string upgradeName : currentUpgrades)
        {
            UpgradeType upgrade = magic_enum::enum_cast<UpgradeType>(upgradeName).value();
            UpgradeManager::unlockUpgrade(upgrade);
        }

        // Get current planet from save data file
        currentPlanet = magic_enum::enum_cast<PlanetType>(static_cast<std::string>(saveData.at("currentPlanet"))).value();

        // Set planet renderer planet type to loaded planet type
        mainPlanetRenderer.setPlanetType(currentPlanet);

        // Give player silver coins loaded from save file
        InventoryManager::addSilverCoins(saveData.at("coins"));

        // Set level stats loaded from save file
        InventoryManager::setCurrentLevel(saveData.at("level").at("value"));
        InventoryManager::setLevelExp(saveData.at("level").at("progress"));
        InventoryManager::setMaxLevelExp(saveData.at("level").at("max"));

        // Set space station orbit angle from save file
        spaceStation.setOrbitAngle(saveData.at("stationOrbitAngle"));

        // Set mission data for all missions, loaded from save file
        for (int i = 0; i < 3; i++)
        {
            MissionManager::setMissionData(i, saveData.at("missions").at(i));
        }

        // Load all asteroid data from save file and create asteroids with data
        std::vector<AsteroidData> asteroidDatas = saveData.at("asteroids");
        for (AsteroidData data : asteroidDatas)
        {
            std::unique_ptr<Asteroid> asteroid = std::make_unique<Asteroid>(sf::Vector2f(data.x, data.y));
            asteroid->setData(data);
            AsteroidManager::insertAsteroid(std::move(asteroid));
        }

        // Sort all asteroids as they have all just been added into the manager in an undefined order
        AsteroidManager::sortAsteroids();

        // Load all enemy ship data from save file and create enemy ships with data
        std::vector<EnemyShipData> enemyShipDatas = saveData.at("enemyShips");
        for (EnemyShipData data : enemyShipDatas)
        {
            EnemyShip ship(data);
            EnemyShipManager::addShip(ship);
        }

        // Load all item pickup data from save file and create item pickups with data
        std::vector<ItemPickupData> itemDatas = saveData.at("itemPickups");
        for (ItemPickupData data : itemDatas)
        {
            ItemPickupManager::addItem(data.type, sf::Vector2f(data.x, data.y));
        }

        // Set player ship data from save file
        playerShip.setPosition(sf::Vector2f(saveData.at("pos").at("x"), saveData.at("pos").at("y")));
        playerShip.setHealth(saveData.at("health"));
        playerShip.setMaxHealth(saveData.at("maxHealth"));

        // Set camera offset from save file
        Camera::setOffset(sf::Vector2f(saveData.at("cam").at("x"), saveData.at("cam").at("y")));

    }
    // If any errors occured during loading data from save file, return corrupt file error
    catch (const std::exception& e)
    {
        // Output error
        std::cout << "ERROR: " << e.what() << std::endl;
        // Return corrupt file error
        return LoadDataSuccess::CORRUPT_FILE;
    }

    // Return successful load outcome by default
    return LoadDataSuccess::SUCCESSFUL;

}

// Save current game data to file
void Game::saveData()
{
    // Create json object to store save data in
	nlohmann::json saveData;

    // Store all inventory items in json object
    for (auto itemPair : itemTextureMap)
    {
        ItemPickupType type = itemPair.first;
        saveData["inventory"][magic_enum::enum_name(type)] = InventoryManager::getItemCount(type);
    }

    // Store all unlocked upgrades in json object
    std::vector<std::string> currentUpgrades;
    for (UpgradeType upgrade : UpgradeManager::getUpgrades())
    {
        std::string_view upgradeName = magic_enum::enum_name(upgrade);
        currentUpgrades.push_back(static_cast<std::string>(upgradeName));
    }
    saveData["upgrades"] = currentUpgrades;

    // Store current planet type in json object
    saveData["currentPlanet"] = static_cast<std::string>(magic_enum::enum_name(currentPlanet));

    // Store coin count in json object
	saveData["coins"] = InventoryManager::getSilverCoins();

    // Store player ship data in json object
	saveData["pos"]["x"] = playerShip.getPosition().x;
	saveData["pos"]["y"] = playerShip.getPosition().y;
    saveData["health"] = playerShip.getHealth();
    saveData["maxHealth"] = playerShip.getMaxHealth();

    // Store camera offset in json object
    saveData["cam"]["x"] = -Camera::getDrawOffset().x;
    saveData["cam"]["y"] = -Camera::getDrawOffset().y;

    // Store level data in json object
    saveData["level"]["value"] = InventoryManager::getCurrentLevel();
    saveData["level"]["progress"] = InventoryManager::getLevelExp();
    saveData["level"]["max"] = InventoryManager::getMaxLevelExp();

    // Store space station orbit angle in json object
    saveData["stationOrbitAngle"] = spaceStation.getOrbitAngle();

    // Store all mission data in json object
    for (int i = 0; i < 3; i++)
    {
        saveData["missions"][i] = MissionManager::getMissionData(i);
    }

    // Store all asteroid data in json object
	std::vector<AsteroidData> asteroidDatas;
	for (std::unique_ptr<Asteroid>& asteroid : AsteroidManager::getAsteroids())
	{
		AsteroidData asteroidData = asteroid->generateData();
		asteroidDatas.push_back(asteroidData);
	}
	saveData["asteroids"] = asteroidDatas;

    // Store all enemy ship data in json object
    std::vector<EnemyShipData> enemyShipDatas;
	for (EnemyShip& EnemyShip : EnemyShipManager::getShips())
	{
		EnemyShipData enemyShipData = EnemyShip.generateData();
		enemyShipDatas.push_back(enemyShipData);
	}
	saveData["enemyShips"] = enemyShipDatas;

    // Store all item pickup data in json object
    std::vector<ItemPickupData> itemDatas;
    for (ItemPickup& item : ItemPickupManager::getPickups())
    {
        ItemPickupData itemData{item.getPosition().x, item.getPosition().y, item.getType()};
        itemDatas.push_back(itemData);
    }
    saveData["itemPickups"] = itemDatas;

    // Attempt to open a new save file in binary format
	std::ofstream file("save.data", std::ios::binary);

    // Convert json object to bson binary data
    std::vector<std::uint8_t> bson_save = nlohmann::json::to_bson(saveData);

    // Write bson binary data to save file
    file.write(reinterpret_cast<const char*>(bson_save.data()), bson_save.size());

    // Close save file
    file.close();

}
