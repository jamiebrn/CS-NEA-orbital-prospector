#include "Game.hpp"

Game::Game()
    : playerShip(sf::Vector2f(0, 0)),
    spaceStation(sf::Vector2f(700, 1200), sf::degrees(0)),
    titlePlanetRenderer(PlanetType::Earth),
    mainPlanetRenderer(PlanetType::Earth),
    playerHealthBar(sf::Vector2f(30, 30), sf::Vector2f(600, 50), 50),
    missionProgress(sf::Vector2f(1600, 200), sf::Vector2f(270, 30), 1),
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

    if (!TextRenderer::loadFont(FONT_PATH))
    {
        std::cout << "ERROR: Font has not been loaded correctly" << std::endl;
        return false;
    }

    auto start = std::chrono::system_clock::now();

    if (!TextureManager::loadTextures(window))
    {
        std::cout << "ERROR: Textures have not been loaded correctly" << std::endl;
        return false;
    }

    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);;
    std::cout << "Loaded textures in " << elapsed.count() << "ms" << '\n';

    start = std::chrono::system_clock::now();

    if (!SoundManager::loadSounds(window))
    {
        std::cout << "ERROR: Sounds have not been loaded correctly" << std::endl;
        return false;
    }

    end = std::chrono::system_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);;
    std::cout << "Loaded sounds in " << elapsed.count() << "ms" << '\n';


    initUI();

    changeState(GameState::MainMenu);

    titleBackgroundSubRectPos = sf::Vector2i(rand() % static_cast<int>(WORLD_WIDTH), rand() % static_cast<int>(WORLD_HEIGHT));

    titlePlanetRenderer.setPosition(sf::Vector2f(WINDOW_WIDTH * 0.8, WINDOW_HEIGHT * 0.85));
    titlePlanetRenderer.setScale(7);

    mainPlanetRenderer.setPosition(sf::Vector2f(1700, 1700));
    mainPlanetRenderer.setScale(7);

    levelBar.setFillColour(sf::Color(255, 239, 1));
    missionProgress.setFillColour(sf::Color(14, 166, 221));

    inStationRange = false;

    travelTime = 0;

    showUIRing = true;
    paused = false;

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

    // Pause menu buttons

    pauseMenuButtons.addButton("resume", {
        sf::Vector2f(WINDOW_WIDTH / 2 - 100, 400), sf::Vector2f(200, 70),
        "Resume", sf::Color(43, 46, 212), sf::Color(53, 56, 222)
    });

    pauseMenuButtons.addButton("save", {
        sf::Vector2f(WINDOW_WIDTH / 2 - 100, 500), sf::Vector2f(200, 70),
        "Save", sf::Color(245, 175, 15), sf::Color(250, 185, 25)
    });

    pauseMenuButtons.addButton("quit", {
        sf::Vector2f(WINDOW_WIDTH / 2 - 100, 600), sf::Vector2f(200, 70),
        "Quit", sf::Color(190, 15, 15), sf::Color(220, 20, 20)
    });

    // Space station menu buttons

    stationMenuButtons.addButton("upgrades", {
        sf::Vector2f(128, 208), sf::Vector2f(820, 100),
        "Upgrades", sf::Color(15, 190, 15), sf::Color(20, 220, 20)
    });

    stationMenuButtons.addButton("market", {
        sf::Vector2f(128, 318), sf::Vector2f(820, 100),
        "Market", sf::Color(15, 190, 15), sf::Color(20, 220, 20)
    });

    stationMenuButtons.addButton("forge", {
        sf::Vector2f(128, 428), sf::Vector2f(820, 100),
        "Forge", sf::Color(15, 190, 15), sf::Color(20, 220, 20)
    });

    stationMenuButtons.addButton("missions", {
        sf::Vector2f(128, 538), sf::Vector2f(820, 100),
        "Missions", sf::Color(15, 190, 15), sf::Color(20, 220, 20)
    });

    stationMenuButtons.addButton("level", {
        sf::Vector2f(128, 648), sf::Vector2f(820, 100),
        "Level", sf::Color(15, 190, 15), sf::Color(20, 220, 20)
    });

    stationMenuButtons.addButton("travel", {
        sf::Vector2f(128, 758), sf::Vector2f(820, 100),
        "Travel", sf::Color(15, 190, 15), sf::Color(20, 220, 20)
    });

    stationMenuButtons.addButton("return", {
        sf::Vector2f(128, 868), sf::Vector2f(820, 100),
        "Return to space", sf::Color(15, 190, 15), sf::Color(20, 220, 20)
    });

    // Space station upgrade buttons

    // Space station market buttons

    stationMarketButtons.addButton("sell1", {
        sf::Vector2f(400, 200), sf::Vector2f(100, 50),
        "x1", sf::Color(15, 190, 15), sf::Color(20, 220, 20)
    });

    stationMarketButtons.addButton("sell25%", {
        sf::Vector2f(510, 200), sf::Vector2f(100, 50),
        "25%", sf::Color(15, 190, 15), sf::Color(20, 220, 20)
    });

    stationMarketButtons.addButton("sell50%", {
        sf::Vector2f(620, 200), sf::Vector2f(100, 50),
        "50%", sf::Color(15, 190, 15), sf::Color(20, 220, 20)
    });

    stationMarketButtons.addButton("sell75%", {
        sf::Vector2f(730, 200), sf::Vector2f(100, 50),
        "75%", sf::Color(15, 190, 15), sf::Color(20, 220, 20)
    });

    stationMarketButtons.addButton("sell100%", {
        sf::Vector2f(840, 200), sf::Vector2f(100, 50),
        "100%", sf::Color(15, 190, 15), sf::Color(20, 220, 20)
    });

    stationMarketButtons.generalData["sellAmount"] = 0;

    // Space station mission buttons

    stationMissionButtons.addButton("mission1", {
        sf::Vector2f(80, 330), sf::Vector2f(450, 140),
        "Mission 1", sf::Color(15, 190, 15), sf::Color(20, 220, 20),
        50
    });

    stationMissionButtons.addButton("mission2", {
        sf::Vector2f(80, 538), sf::Vector2f(450, 140),
        "Mission 2", sf::Color(15, 190, 15), sf::Color(20, 220, 20),
        50
    });

    stationMissionButtons.addButton("mission3", {
        sf::Vector2f(80, 746), sf::Vector2f(450, 140),
        "Mission 3", sf::Color(15, 190, 15), sf::Color(20, 220, 20),
        50
    });

    // Space station level buttons

    stationLevelButtons.addButton("levelUp", {
        sf::Vector2f(200, 800), sf::Vector2f(200, 70),
        "Level Up", sf::Color(15, 190, 15), sf::Color(20, 220, 20)
    });

}