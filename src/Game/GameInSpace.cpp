#include "Game.hpp"

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
            {
                saveData();
                window.close();
            }

            if (event.key.code == sf::Keyboard::E)
            {
                if (inStationRange)
                    changeState(GameState::InStation);
            }

            if (event.key.code == sf::Keyboard::H)
                showUIRing = !showUIRing;

        }

    }

    

    // Logic

    float deltaTime = clock.restart().asSeconds();

    sf::Vector2f drawOffset = Camera::getDrawOffset();

    sf::Vector2i screenMousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = window.mapPixelToCoords(screenMousePosition);

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

    text = std::to_string(drawOffset.x) + ", " + std::to_string(drawOffset.y);
    TextRenderer::drawText(window, {text, sf::Vector2f(20, 65), sf::Color(255, 255, 255), 25, sf::Color(0, 0, 0), 1});

    if (inStationRange)
    {
        text = "Enter Station (E)";
        TextRenderer::drawText(window, {text, sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 * 3), sf::Color(255, 255, 255), 50, sf::Color(0, 0, 0), 3, true});
    }

    if (showUIRing)
        UIRingManager::draw(window);


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
