#include "Game.hpp"

Game::Game()
    : playerShip(sf::Vector2f(0, 0)),
    spaceStation(sf::Vector2f(700, 1200), sf::degrees(0)),
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

    InventoryManager::resetSilverCoins();

    playerShip.setPosition(sf::Vector2f(5000, 5000));

    std::ifstream file("save.json");
    if (!file.fail())
    {
        nlohmann::json saveData;
        file >> saveData;

        InventoryManager::addItem(ItemPickupType::Rock, saveData["rock"]);
        InventoryManager::addItem(ItemPickupType::CopperChunk, saveData["copper"]);
        InventoryManager::addItem(ItemPickupType::IronChunk, saveData["iron"]);
        InventoryManager::addSilverCoins(saveData["coins"]);

		std::vector<AsteroidData> asteroidDatas = saveData["asteroids"];
		for (AsteroidData data : asteroidDatas)
		{
			Asteroid asteroid(sf::Vector2f(data.x, data.y));
			asteroid.setData(data);
			AsteroidManager::insertAsteroid(asteroid);
		}

        playerShip.setPosition(sf::Vector2f(saveData["pos"]["x"], saveData["pos"]["y"]));
    }
    else
    {
        for (int i = 0; i < 1000; i++)
        {
            sf::Vector2f position(rand() % static_cast<int>(WORLD_WIDTH), rand() % static_cast<int>(WORLD_HEIGHT));
            AsteroidManager::createAsteroid(position);
        }
    }

    mainPlanetRenderer.setPosition(sf::Vector2f(1700, 1700));
    mainPlanetRenderer.setScale(7);

    inStationRange = false;

    showUIRing = true;

    return true;

}

void Game::mainLoop()
{

    Camera::setOffset(sf::Vector2f(4500, 4000));

    EnemyShipManager::addShip(sf::Vector2f(5000, 4500));

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

    gameState = newState;

}

void Game::saveData()
{

	nlohmann::json saveData;
	saveData["rock"] = InventoryManager::getItemCount(ItemPickupType::Rock);
	saveData["copper"] = InventoryManager::getItemCount(ItemPickupType::CopperChunk);
	saveData["iron"] = InventoryManager::getItemCount(ItemPickupType::IronChunk);
	saveData["coins"] = InventoryManager::getSilverCoins();
	saveData["pos"]["x"] = playerShip.getPosition().x;
	saveData["pos"]["y"] = playerShip.getPosition().x;

	std::vector<AsteroidData> asteroidDatas;
	for (Asteroid& asteroid : AsteroidManager::getAsteroids())
	{
		AsteroidData asteroidData = asteroid.generateData();
		asteroidDatas.push_back(asteroidData);
	}
	saveData["asteroids"] = asteroidDatas;

	std::ofstream file("save.json");
	file << saveData << std::endl;

}
