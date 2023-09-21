#include "Game.hpp"

Game::Game()
    : playerShip(sf::Vector2f(0, 0)),
    spaceStation(sf::Vector2f(700, 1200), sf::degrees(0)),
    titlePlanetRenderer(PlanetType::Earth),
    mainPlanetRenderer(PlanetType::Earth),
    levelBar(sf::Vector2f(WINDOW_WIDTH / 2 - 300, 30), sf::Vector2f(600, 50), 50),
    view(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))
{}

bool Game::initialise()
{

    srand((unsigned)time(0));

    sf::Vector2u monitorRes = sf::VideoMode::getDesktopMode().size;
    window.create(sf::VideoMode(monitorRes), WINDOW_TITLE, sf::Style::Fullscreen);

    window.setFramerateLimit(240);

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

    initUI();

    changeState(GameState::MainMenu);

    titleBackgroundSubRectPos = sf::Vector2i(rand() % static_cast<int>(WORLD_WIDTH), rand() % static_cast<int>(WORLD_HEIGHT));

    titlePlanetRenderer.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.8, WINDOW_HEIGHT * 0.85));
    titlePlanetRenderer.setScale(7);

    mainPlanetRenderer.setPosition(sf::Vector2f(1700, 1700));
    mainPlanetRenderer.setScale(7);

    levelBar.setFillColour(sf::Color(255, 239, 1));

    inStationRange = false;

    showUIRing = true;
    paused = false;
    savedSincePause = false;

    loadDataError = false;

    return true;

}

void Game::initUI()
{

    // Title screen buttons

    titleButtons.addButton("new", {
        sf::Vector2f(WINDOW_WIDTH / 2 - 100, 700), sf::Vector2f(200, 70),
        "New", sf::Color(15, 190, 15), sf::Color(20, 220, 20)
    });

    titleButtons.addButton("load", {
        sf::Vector2f(WINDOW_WIDTH / 2 - 100, 800), sf::Vector2f(200, 70),
        "Load", sf::Color(15, 15, 190), sf::Color(20, 20, 220)
    });

    titleButtons.addButton("quit", {
        sf::Vector2f(WINDOW_WIDTH / 2 - 100, 900), sf::Vector2f(200, 70),
        "Quit", sf::Color(190, 15, 15), sf::Color(220, 20, 20)
    });

    // Space station menu buttons

    stationMenuButtons.addButton("upgrades", {
        sf::Vector2f(WINDOW_WIDTH / 2 - 100, 500), sf::Vector2f(200, 70),
        "Upgrades", sf::Color(15, 190, 15), sf::Color(20, 220, 20)
    });

    stationMenuButtons.addButton("market", {
        sf::Vector2f(WINDOW_WIDTH / 2 - 100, 600), sf::Vector2f(200, 70),
        "Market", sf::Color(15, 190, 15), sf::Color(20, 220, 20)
    });

    stationMenuButtons.addButton("missions", {
        sf::Vector2f(WINDOW_WIDTH / 2 - 100, 700), sf::Vector2f(200, 70),
        "Missions", sf::Color(15, 190, 15), sf::Color(20, 220, 20)
    });

    stationMenuButtons.addButton("level", {
        sf::Vector2f(WINDOW_WIDTH / 2 - 100, 800), sf::Vector2f(200, 70),
        "Level", sf::Color(15, 190, 15), sf::Color(20, 220, 20)
    });

}