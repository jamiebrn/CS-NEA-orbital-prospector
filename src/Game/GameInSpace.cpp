#include "Game.hpp"

void Game::inSpaceLoop()
{

    sf::Vector2i screenMousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = window.mapPixelToCoords(screenMousePosition);

    // Pause menu UI
    UIButton saveButton;
    UIButton quitButton;
    if (paused)
    {
        saveButton.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 100, 600));
        saveButton.setSize(sf::Vector2f(200, 70));
        saveButton.setText("Save");
        if (savedSincePause)
            saveButton.setText("Saved!");
        saveButton.setColour(sf::Color(245, 175, 15));
        saveButton.setHoverColour(sf::Color(250, 185, 25));
        saveButton.update(mousePosition);

        quitButton.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 100, 700));
        quitButton.setSize(sf::Vector2f(200, 70));
        quitButton.setText("Quit");
        quitButton.setColour(sf::Color(190, 15, 15));
        quitButton.setHoverColour(sf::Color(220, 20, 20));
        quitButton.update(mousePosition);
    }

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
                paused = !paused;
                savedSincePause = false;
            }

            if (event.key.code == sf::Keyboard::E)
            {
                if (inStationRange)
                    changeState(GameState::InStation);
            }

            if (event.key.code == sf::Keyboard::H)
                showUIRing = !showUIRing;

        }

        if (paused)
        {
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left && saveButton.isHovering())
                {
                    saveData();
                    savedSincePause = true;
                }
                if (event.mouseButton.button == sf::Mouse::Left && quitButton.isHovering())
                {
                    changeState(GameState::MainMenu);
                }
            }
        }

    }

    

    // Logic

    float deltaTime = clock.restart().asSeconds();
    sf::Vector2f drawOffset = Camera::getDrawOffset();

    if (!paused)
    {

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

        levelBar.setMaxValue(InventoryManager::getMaxLevelExp());
        levelBar.updateValue(InventoryManager::getLevelExp());
        levelBar.update(deltaTime);

        Camera::update(playerShip.getPosition(), deltaTime);

    }



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
    
    levelBar.draw(window);
    std::string text = "Level " + std::to_string(InventoryManager::getCurrentLevel());
    TextRenderer::drawText(window, {text, sf::Vector2f(WINDOW_WIDTH / 2, 65), sf::Color(255, 255, 255), 32, sf::Color(0, 0, 0), 3, true, true});

    text = std::to_string(static_cast<int>(levelBar.getValue())) + " / " + std::to_string(static_cast<int>(levelBar.getMaxValue()));
    TextRenderer::drawText(window, {text, sf::Vector2f(WINDOW_WIDTH / 2, 85), sf::Color(255, 255, 255), 24, sf::Color(0, 0, 0), 1, true, true});

    text = std::to_string(static_cast<int>(1 / deltaTime)) + " FPS";
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
    
    

    // Pause menu

    if (paused)
    {

        sf::RectangleShape background(sf::Vector2f(300, 400));
        background.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 200));
        background.setFillColor(sf::Color(20, 20, 20, 150));

        window.draw(background);
        saveButton.draw(window);
        quitButton.draw(window);

    }

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
