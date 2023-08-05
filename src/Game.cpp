#include "Game.hpp"

Game::Game()
    : playerShip(sf::Vector2f(0, 0)),
    spaceStation(sf::Vector2f(700, 1200), sf::degrees(0)),
    mainPlanetRenderer(PlanetType::Earth)
{}

bool Game::initialise()
{

    srand((unsigned)time(0));

    window.create(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close);

    window.setFramerateLimit(200);

    if (!iconImage.loadFromFile(ICON_PATH))
    {
        std::cout << "ERROR: Cannot load window icon" << std::endl;
        return false;
    }
    window.setIcon(iconImage.getSize(), iconImage.getPixelsPtr());

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

    gameState = GameState::InSpace;

    mainPlanetRenderer.setPosition(sf::Vector2f(1700, 1700));
    mainPlanetRenderer.setScale(6);

    inStationRange = false;

    showUIRing = true;

    return true;

}

void Game::mainLoop()
{

    Camera::setOffset(sf::Vector2f(900, 900));

    playerShip.setPosition(sf::Vector2f(5000, 5000));

    EnemyShipManager::addShip(sf::Vector2f(5000, 4500));

    for (int i = 0; i < 1000; i++)
    {
        sf::Vector2f position(rand() % static_cast<int>(WORLD_WIDTH), rand() % static_cast<int>(WORLD_HEIGHT));
        AsteroidManager::createAsteroid(position);
    }

    SoundManager::playMusic(MusicType::Track1);

    while (window.isOpen())
    {

        switch (gameState)
        {
        
        case GameState::InSpace:

            inSpaceLoop();
            break;
        
        case GameState::InStation:
            inStationLoop();
            break;
        
        }

    }

}

void Game::inSpaceLoop()
{

    // Event handling
        
    sf::Event event;
    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::Closed)
            window.close();
        
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();

            if (event.key.code == sf::Keyboard::E)
            {
                if (inStationRange)
                    gameState = GameState::InStation;
            }

            if (event.key.code == sf::Keyboard::H)
                showUIRing = !showUIRing;

        }

    }

    

    // Logic

    float deltaTime = clock.restart().asSeconds();

    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    sf::Vector2f drawOffset = Camera::getDrawOffset();

    playerShip.update(deltaTime, mousePosition);

    EnemyShipManager::updateShips(playerShip.getPosition(), deltaTime);

    BulletManager::updateBullets(deltaTime);

    AsteroidManager::updateAsteroids(deltaTime);

    float unprojectMult = Helper::unprojectDepthMultipier(PLANET_DEPTH_DIVIDE, SPACE_STATION_DEPTH_DIVIDE);
    sf::Vector2f planetCentre = mainPlanetRenderer.getPosition();
    planetCentre += drawOffset * unprojectMult;

    spaceStation.orbitBody(planetCentre, 1400, 1, deltaTime);

    if (distanceSqToStation() <= STATION_MAX_RANGE * STATION_MAX_RANGE)
    {
        inStationRange = true;
    }
    else
    {
        inStationRange = false;
    }

    mainPlanetRenderer.update(deltaTime);

    unprojectMult = Helper::unprojectDepthMultipier(SPACE_STATION_DEPTH_DIVIDE, 1);
    sf::Vector2f spaceStationPos = spaceStation.getPosition() + drawOffset * unprojectMult;

    UIRingManager::update(spaceStationPos, EnemyShipManager::getShips());

    Camera::update(playerShip.getPosition(), deltaTime);



    // Render

    window.clear();

    TextureDrawData backgroundData = {TextureType::EarthBackground, drawOffset / BACKGROUND_DEPTH_DIVIDE, sf::degrees(0), 3, false};
    TextureManager::drawSubTexture(window, backgroundData, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(WORLD_WIDTH, WORLD_HEIGHT)));

    mainPlanetRenderer.draw(window);

    spaceStation.draw(window);

    ItemPickupManager::drawPickups(window);

    AsteroidManager::drawAsteroids(window);

    BulletManager::drawBullets(window);

    EnemyShipManager::drawShips(window);

    playerShip.draw(window);



    // UI

    std::string text = std::to_string(static_cast<int>(1 / deltaTime)) + " FPS";
    TextRenderer::drawText(window, {text, sf::Vector2f(20, 5), sf::Color(255, 255, 255), 25, sf::Color(0, 0, 0), 1});

    text = std::to_string(BulletManager::getBulletCount()) + " Bullets";
    TextRenderer::drawText(window, {text, sf::Vector2f(20, 25), sf::Color(255, 255, 255), 25, sf::Color(0, 0, 0), 1});

    text = std::to_string(AsteroidManager::getAsteroids().size()) + " Asteroids";
    TextRenderer::drawText(window, {text, sf::Vector2f(20, 45), sf::Color(255, 255, 255), 25, sf::Color(0, 0, 0), 1});

    if (inStationRange)
    {
        text = "Enter Station (E)";
        TextRenderer::drawText(window, {text, sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 * 3), sf::Color(255, 255, 255), 50, sf::Color(0, 0, 0), 3, true});
    }

    if (showUIRing)
        UIRingManager::draw(window);


    window.display();

}

void Game::inStationLoop()
{

    sf::Event event;
    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::Closed)
            window.close();
        
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                gameState = GameState::InSpace;
        }

    }

    float deltaTime = clock.restart().asSeconds();

    window.clear(sf::Color(40, 40, 220));

    std::string text = "Space Station";
    TextRenderer::drawText(window, {text, sf::Vector2f(WINDOW_WIDTH / 2, 80), sf::Color(255, 255, 255), 80, sf::Color(0, 0, 0), 3, true});

    TextureDrawData drawData = {
        TextureType::PickupRock,
        sf::Vector2f(300, 400),
        sf::degrees(0),
        5,
        false
    };

    TextureManager::drawTexture(window, drawData);

    text = std::to_string(InventoryManager::getItemCount(ItemPickupType::Rock));
    TextRenderer::drawText(window, {text, sf::Vector2f(370, 410), sf::Color(255, 255, 255), 50, sf::Color(0, 0, 0), 3});

    text = "Exit (ESC)";
    TextRenderer::drawText(window, {text, sf::Vector2f(20, 600), sf::Color(255, 255, 255), 50, sf::Color(0, 0, 0), 3});

    window.display();

}

float Game::distanceSqToStation()
{

    sf::Vector2f drawOffset = Camera::getDrawOffset();
    float unprojStation = Helper::unprojectDepthMultipier(SPACE_STATION_DEPTH_DIVIDE, 1);

    sf::Vector2f stationPos = spaceStation.getPosition();
    stationPos += drawOffset * unprojStation;

    float distanceSq = (playerShip.getPosition() - stationPos).lengthSq();

    return distanceSq;

}
