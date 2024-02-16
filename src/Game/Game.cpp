#include "Game.hpp"

void Game::mainLoop()
{

    while (window.isOpen())
    {

        switch (gameState)
        {

		case GameState::MainMenu:
			inMainMenuLoop();
			break;
		
		case GameState::InSpace:
			inSpaceLoop();
			break;
		
		case GameState::InStation:
			inStationLoop();
			break;

        }

    }

}

void Game::changeState(GameState newState)
{

    if (newState == GameState::InStation)
    {
        stationMenuState = StationMenuState::Main;
    }
    else if (newState == GameState::MainMenu)
    {
        Camera::setOffset(sf::Vector2f(0, 0));
        SoundManager::playMusic(MusicType::Menu);
    }
    else if (newState == GameState::InSpace && gameState == GameState::MainMenu)
    {
        SoundManager::playMusic(MusicType::Track1);
    }

    gameState = newState;

}

LoadDataSuccess Game::loadData()
{

    std::ifstream file("Data/save.json");
    if (file.fail())
        return LoadDataSuccess::NO_FILE;

    try
    {

        nlohmann::json saveData;
        file >> saveData;

        InventoryManager::addItem(ItemPickupType::Rock, saveData.at("rock"));
        InventoryManager::addItem(ItemPickupType::CopperChunk, saveData.at("copper"));
        InventoryManager::addItem(ItemPickupType::IronChunk, saveData.at("iron"));
        InventoryManager::addSilverCoins(saveData.at("coins"));

        InventoryManager::setCurrentLevel(saveData.at("level").at("value"));
        InventoryManager::setLevelExp(saveData.at("level").at("progress"));
        InventoryManager::setMaxLevelExp(saveData.at("level").at("max"));

        for (int i = 0; i < 3; i++)
        {
            MissionManager::setMissionData(i, saveData.at("missions").at(i));
        }

        std::vector<AsteroidData> asteroidDatas = saveData.at("asteroids");
        for (AsteroidData data : asteroidDatas)
        {
            std::unique_ptr<Asteroid> asteroid = std::make_unique<Asteroid>(sf::Vector2f(data.x, data.y));
            asteroid->setData(data);
            AsteroidManager::insertAsteroid(std::move(asteroid));
        }

        std::vector<EnemyShipData> enemyShipDatas = saveData.at("enemyShips");
        for (EnemyShipData data : enemyShipDatas)
        {
            EnemyShip ship(data);
            EnemyShipManager::addShip(ship);
        }

        std::vector<ItemPickupData> itemDatas = saveData.at("itemPickups");
        for (ItemPickupData data : itemDatas)
        {
            ItemPickupManager::addItem(data.type, sf::Vector2f(data.x, data.y));
        }

        playerShip.setPosition(sf::Vector2f(saveData.at("pos").at("x"), saveData.at("pos").at("y")));
        playerShip.setHealth(saveData.at("health"));
        playerShip.setMaxHealth(saveData.at("maxHealth"));

        Camera::setOffset(sf::Vector2f(saveData.at("cam").at("x"), saveData.at("cam").at("y")));

    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
        return LoadDataSuccess::CORRUPT_FILE;
    }

    return LoadDataSuccess::SUCCESSFUL;

}

void Game::saveData()
{

	nlohmann::json saveData;
    
	saveData["rock"] = InventoryManager::getItemCount(ItemPickupType::Rock);
	saveData["copper"] = InventoryManager::getItemCount(ItemPickupType::CopperChunk);
	saveData["iron"] = InventoryManager::getItemCount(ItemPickupType::IronChunk);
	saveData["coins"] = InventoryManager::getSilverCoins();

	saveData["pos"]["x"] = playerShip.getPosition().x;
	saveData["pos"]["y"] = playerShip.getPosition().y;
    saveData["health"] = playerShip.getHealth();
    saveData["maxHealth"] = playerShip.getMaxHealth();

    saveData["cam"]["x"] = -Camera::getDrawOffset().x;
    saveData["cam"]["y"] = -Camera::getDrawOffset().y;

    saveData["level"]["value"] = InventoryManager::getCurrentLevel();
    saveData["level"]["progress"] = InventoryManager::getLevelExp();
    saveData["level"]["max"] = InventoryManager::getMaxLevelExp();

    for (int i = 0; i < 3; i++)
    {
        saveData["missions"][i] = MissionManager::getMissionData(i);
    }

	std::vector<AsteroidData> asteroidDatas;
	for (std::unique_ptr<Asteroid>& asteroid : AsteroidManager::getAsteroids())
	{
		AsteroidData asteroidData = asteroid->generateData();
		asteroidDatas.push_back(asteroidData);
	}
	saveData["asteroids"] = asteroidDatas;

    std::vector<EnemyShipData> enemyShipDatas;
	for (EnemyShip& EnemyShip : EnemyShipManager::getShips())
	{
		EnemyShipData enemyShipData = EnemyShip.generateData();
		enemyShipDatas.push_back(enemyShipData);
	}
	saveData["enemyShips"] = enemyShipDatas;

    std::vector<ItemPickupData> itemDatas;
    for (ItemPickup& item : ItemPickupManager::getPickups())
    {
        ItemPickupData itemData{item.getPosition().x, item.getPosition().y, item.getType()};
        itemDatas.push_back(itemData);
    }
    saveData["itemPickups"] = itemDatas;

	std::ofstream file("Data/save.json");
	file << saveData << std::endl;

}
