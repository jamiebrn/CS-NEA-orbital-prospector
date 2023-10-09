#include "Game.hpp"

void Game::inSpaceLoop()
{

    sf::Vector2i screenMousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = window.mapPixelToCoords(screenMousePosition);


    // Event handling

    bool leftMousePressed = false;
        
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
                pauseMenuButtons.setButtonText("save", "Save");
            }

            if (event.key.code == sf::Keyboard::E)
            {
                if (inStationRange)
                    changeState(GameState::InStation);
            }

            if (event.key.code == sf::Keyboard::H)
                showUIRing = !showUIRing;
            
            if (event.key.code == sf::Keyboard::G)
            {
                sf::Vector2f pos = mousePosition - Camera::getDrawOffset();
                EnemyShipManager::addShip(EnemyShip(pos));
            }

        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
                leftMousePressed = true;
        }

    }


    if (paused && leftMousePressed)
    {
        if (pauseMenuButtons.isButtonPressed("resume"))
        {
            paused = false;
        }
        else if (pauseMenuButtons.isButtonPressed("save"))
        {
            saveData();
            pauseMenuButtons.setButtonText("save", "Saved!");
        }
        else if (pauseMenuButtons.isButtonPressed("quit"))
        {
            changeState(GameState::MainMenu);
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
        BulletManager::updateEnemyBullets(deltaTime);

        AsteroidManager::updateAsteroids(deltaTime);

        float unprojectMult = Helper::unprojectDepthMultipier(PLANET_DEPTH_DIVIDE, SPACE_STATION_DEPTH_DIVIDE);
        sf::Vector2f planetCentre = mainPlanetRenderer.getPosition();
        planetCentre += drawOffset * unprojectMult;

        spaceStation.orbitBody(planetCentre, 1400, 1, deltaTime);

        inStationRange = (distanceSqToStation() <= STATION_MAX_RANGE * STATION_MAX_RANGE);

        mainPlanetRenderer.update(deltaTime);

        unprojectMult = Helper::unprojectDepthMultipier(SPACE_STATION_DEPTH_DIVIDE, 1);
        sf::Vector2f spaceStationPos = spaceStation.getPosition() + drawOffset * unprojectMult;

        UIRingManager::update(spaceStationPos, EnemyShipManager::getShips());

        playerHealthBar.setMaxValue(playerShip.getMaxHealth());
        playerHealthBar.setWidth(playerShip.getMaxHealth() * 9);
        playerHealthBar.updateValue(playerShip.getHealth());
        playerHealthBar.update(deltaTime);

        levelBar.setMaxValue(InventoryManager::getMaxLevelExp());
        levelBar.updateValue(InventoryManager::getLevelExp());
        levelBar.update(deltaTime);

        Camera::update(playerShip.getPosition(), deltaTime);

    }
    else
    {
        pauseMenuButtons.update(mousePosition);
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
    BulletManager::drawEnemyBullets(window);

    EnemyShipManager::drawShips(window);

    playerShip.draw(window);



    // UI

    if (playerShip.isAlive())
    {
    
        playerHealthBar.draw(window);
        std::string text = std::to_string(playerShip.getHealth()) + " / " + std::to_string(playerShip.getMaxHealth()) + " HP";
        TextRenderer::drawText(window, {
            text, sf::Vector2f(50, 55),
            sf::Color(255, 255, 255), 32, sf::Color(0, 0, 0), 3,
            false, true
        });

        levelBar.draw(window);

        text = ("Level " + std::to_string(InventoryManager::getCurrentLevel())
            + " - " + std::to_string(static_cast<int>(levelBar.getValue())) + " / " + 
            std::to_string(static_cast<int>(levelBar.getMaxValue())) + " XP");
            
        TextRenderer::drawText(window, {
            text, sf::Vector2f(WINDOW_WIDTH / 2, 55),
            sf::Color(255, 255, 255), 32, sf::Color(0, 0, 0), 3,
            true, true
        });

        if (inStationRange)
        {
            text = "Enter Station (E)";
            TextRenderer::drawText(window, {
                text, sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 4 * 3),
                sf::Color(255, 255, 255), 50, sf::Color(0, 0, 0), 3, true
            });
        }

        if (showUIRing)
            UIRingManager::draw(window);
        
    }
    else
    {
        std::string text = "You died";
        TextRenderer::drawText(window, {
            text, sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
            sf::Color(255, 255, 255), 72, sf::Color(0, 0, 0), 4,
            true, true
        });
    }

    
    std::string text = std::to_string(static_cast<int>(1 / deltaTime)) + " FPS";
    TextRenderer::drawText(window, {text, sf::Vector2f(20, 155), sf::Color(255, 255, 255), 25, sf::Color(0, 0, 0), 1});

    text = std::to_string(BulletManager::getBulletCount()) + " Bullets";
    TextRenderer::drawText(window, {text, sf::Vector2f(20, 175), sf::Color(255, 255, 255), 25, sf::Color(0, 0, 0), 1});

    text = std::to_string(AsteroidManager::getAsteroids().size()) + " Asteroids";
    TextRenderer::drawText(window, {text, sf::Vector2f(20, 195), sf::Color(255, 255, 255), 25, sf::Color(0, 0, 0), 1});
    

    // Pause menu

    if (paused)
    {

        sf::RectangleShape background(sf::Vector2f(300, 400));
        background.setPosition(sf::Vector2f(WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 - 200));
        background.setFillColor(sf::Color(20, 20, 20, 150));

        window.draw(background);

        pauseMenuButtons.draw(window);

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
