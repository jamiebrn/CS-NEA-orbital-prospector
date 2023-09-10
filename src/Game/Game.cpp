#include "Game.hpp"

Game::Game()
    : playerShip(sf::Vector2f(0, 0)),
    spaceStation(sf::Vector2f(700, 1200), sf::degrees(0)),
    titlePlanetRenderer(PlanetType::Earth),
    mainPlanetRenderer(PlanetType::Earth),
    view(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))
{}

bool Game::initialise()
{

    srand((unsigned)time(0));

    sf::Vector2u monitorRes = sf::VideoMode::getDesktopMode().size;
    window.create(sf::VideoMode(monitorRes), WINDOW_TITLE, sf::Style::Fullscreen);

    //window.setFramerateLimit(200);

    if (!iconImage.loadFromFile(ICON_PATH))
    {
        std::cout << "ERROR: Cannot load window icon" << std::endl;
        return false;
    }
    window.setIcon(iconImage.getSize(), iconImage.getPixelsPtr());

    window.setView(view);

    if (!TextureManager::loadTextures())
    {
        std::cout << "ERROR: Textures have not been loaded correctly" << std::endl;
        return false;
    }

    if (!SoundManager::loadSounds())
    {
        std::cout << "ERROR: Sounds have not been loaded correctly" << std::endl;
        return false;
    }

    if (!TextRenderer::loadFont(FONT_PATH))
    {
        std::cout << "ERROR: Font has not been loaded correctly" << std::endl;
        return false;
    }

    changeState(GameState::MainMenu);

    titleBackgroundSubRectPos = sf::Vector2i(rand() % static_cast<int>(WORLD_WIDTH), rand() % static_cast<int>(WORLD_HEIGHT));

    titlePlanetRenderer.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.8, WINDOW_HEIGHT * 0.85));
    titlePlanetRenderer.setScale(7);

    mainPlanetRenderer.setPosition(sf::Vector2f(1700, 1700));
    mainPlanetRenderer.setScale(7);

    inStationRange = false;

    showUIRing = true;
    paused = false;
    savedSincePause = false;

    loadDataError = false;

    return true;

}

void Game::mainLoop()
{

    SoundManager::playMusic(MusicType::Track1);

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
    }

    gameState = newState;

}

LoadDataSuccess Game::loadData()
{

    std::ifstream file("save.json");
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

        std::vector<AsteroidData> asteroidDatas = saveData.at("asteroids");
        for (AsteroidData data : asteroidDatas)
        {
            Asteroid asteroid(sf::Vector2f(data.x, data.y));
            asteroid.setData(data);
            AsteroidManager::insertAsteroid(asteroid);
        }

        std::vector<ItemPickupData> itemDatas = saveData.at("itemPickups");
        for (ItemPickupData data : itemDatas)
        {
            ItemPickupManager::addItem(data.type, sf::Vector2f(data.x, data.y));
        }

        playerShip.setPosition(sf::Vector2f(saveData.at("pos").at("x"), saveData.at("pos").at("y")));

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
    saveData["cam"]["x"] = -Camera::getDrawOffset().x;
    saveData["cam"]["y"] = -Camera::getDrawOffset().y;

	std::vector<AsteroidData> asteroidDatas;
	for (Asteroid& asteroid : AsteroidManager::getAsteroids())
	{
		AsteroidData asteroidData = asteroid.generateData();
		asteroidDatas.push_back(asteroidData);
	}
	saveData["asteroids"] = asteroidDatas;

    std::vector<ItemPickupData> itemDatas;
    for (ItemPickup& item : ItemPickupManager::getPickups())
    {
        ItemPickupData itemData{item.getPosition().x, item.getPosition().y, item.getType()};
        itemDatas.push_back(itemData);
    }
    saveData["itemPickups"] = itemDatas;

	std::ofstream file("save.json");
	file << saveData << std::endl;

}
