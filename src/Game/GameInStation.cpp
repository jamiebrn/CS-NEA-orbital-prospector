#include "Game.hpp"

void Game::inStationLoop()
{

    // UI
    sf::Vector2i screenMousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = window.mapPixelToCoords(screenMousePosition);

    std::vector<UISellItemBar> sellItemBars;
    UIButton acceptCompleteMissionButton;

    switch (stationMenuState)
    {

    case StationMenuState::Main:
        stationMenuButtons.update(mousePosition);
        break;
    
    case StationMenuState::Upgrades:
        stationUpgradeButtons.update(mousePosition);
        break;

    case StationMenuState::Market:
    {
        int yOffset = 0;
        for (auto itemTypePair : itemTextureMap)
        {

            ItemPickupType itemType = itemTypePair.first;

            UISellItemBar sellItemBar(itemType);
            sellItemBar.setPosition(sf::Vector2f(400, 300 + yOffset));
            sellItemBar.update(mousePosition);

            sellItemBars.push_back(sellItemBar);

            yOffset += 125;

        }
        break;
    }
    
    case StationMenuState::Missons:
        stationMissionButtons.update(mousePosition);

        acceptCompleteMissionButton.setPosition(sf::Vector2f(1125, 850));
        acceptCompleteMissionButton.setSize(sf::Vector2f(200, 70));
        acceptCompleteMissionButton.setText("Accept mission");
        if (MissionManager::missionCompleted())
            acceptCompleteMissionButton.setText("Complete mission");
        acceptCompleteMissionButton.setColour(sf::Color(15, 190, 15));
        acceptCompleteMissionButton.setHoverColour(sf::Color(20, 220, 20));
        acceptCompleteMissionButton.update(mousePosition);

        break;
    
    case StationMenuState::Level:
        stationLevelButtons.update(mousePosition);
        break;

    }

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
                if (stationMenuState == StationMenuState::Main)
                {
                    changeState(GameState::InSpace);
                }
                else
                {
                    stationMenuState = StationMenuState::Main;
                }
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                leftMousePressed = true;
            }
        }

    }


    if (leftMousePressed)
    {
        switch (stationMenuState)
        {

        case StationMenuState::Main:

            if (stationMenuButtons.isButtonPressed("upgrades"))
            {
                stationMenuState = StationMenuState::Upgrades;
            }
            else if (stationMenuButtons.isButtonPressed("market"))
            {
                stationMenuState = StationMenuState::Market;
            }
            else if (stationMenuButtons.isButtonPressed("missions"))
            {
                selectedMission = -1;

                for (int i = 0; i < 3; i++)
                {
                    std::string title = MissionManager::getMissionData(i).title;
                    stationMissionButtons.setButtonText("mission" + std::to_string(i + 1), title);
                }

                stationMenuState = StationMenuState::Missons;
            }
            else if (stationMenuButtons.isButtonPressed("level"))
            {
                stationMenuState = StationMenuState::Level;
            }

            break;
        
        case StationMenuState::Upgrades:

            if (stationUpgradeButtons.isButtonPressed("health"))
            {
                int health = playerShip.getMaxHealth() + 5;
                health = std::min(health, 80);
                playerShip.setMaxHealth(health);
            }

            break;

        case StationMenuState::Market:

            for (UISellItemBar& sellItemBar : sellItemBars)
            {
                if (sellItemBar.sellButtonHovering())
                {
                    ItemPickupType itemType = sellItemBar.getPickupType();
                    int itemCount = InventoryManager::getItemCount(itemType);

                    InventoryManager::sellItems(itemType, itemCount);
                }
            }

            break;
        
        case StationMenuState::Missons:

            for (int i = 0; i < 3; i++)
            {
                if (stationMissionButtons.isButtonPressed("mission" + std::to_string(i + 1)))
                {
                    selectedMission = i;
                }
            }

            if (acceptCompleteMissionButton.isHovering() && !MissionManager::hasAcceptedMission())
            {
                if (selectedMission != -1)
                {
                    MissionManager::acceptMission(selectedMission);
                }
            }
            if (acceptCompleteMissionButton.isHovering() && MissionManager::missionCompleted())
            {
                MissionManager::completeMission();

                for (int i = 0; i < 3; i++)
                {
                    std::string title = MissionManager::getMissionData(i).title;
                    stationMissionButtons.setButtonText("mission" + std::to_string(i + 1), title);
                }

                selectedMission = -1;
            }

            break;
        
        case StationMenuState::Level:

            break;

        }
    }


    float deltaTime = clock.restart().asSeconds();

    window.clear(sf::Color(40, 40, 220));

    std::string text = "Space Station";
    TextRenderer::drawText(window, {text, sf::Vector2f(WINDOW_WIDTH / 2, 80), sf::Color(255, 255, 255), 100, sf::Color(0, 0, 0), 4, true});

    switch (stationMenuState)
    {
    
    case StationMenuState::Main:
        stationMenuButtons.draw(window);
        break;
    
    case StationMenuState::Upgrades:
        stationUpgradeButtons.draw(window);
        break;

    case StationMenuState::Market:
    {

        for (UISellItemBar& sellItemBar : sellItemBars)
        {
            sellItemBar.draw(window);
        }

        TextureDrawData drawData = {
            TextureType::SilverCoin,
            sf::Vector2f(200, 250),
            sf::degrees(0),
            5,
            false
        };

        TextureManager::drawTexture(window, drawData);

        text = std::to_string(InventoryManager::getSilverCoins());
        TextRenderer::drawText(window, {text, sf::Vector2f(270, 260), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3});
        
        break;
    }
    
    case StationMenuState::Missons:
    {
        stationMissionButtons.draw(window);

        sf::RectangleShape missionBg(sf::Vector2f(1260, 800));
        missionBg.setPosition(sf::Vector2f(595, 220));
        missionBg.setFillColor(sf::Color(40, 40, 40, 130));
        window.draw(missionBg);

        std::string missionTitle = "Mission Info";
        std::string missionDesc = "Select mission for more info";
        if (selectedMission != -1)
        {
            missionTitle = MissionManager::getMissionData(selectedMission).title;
            missionDesc = MissionManager::getMissionData(selectedMission).description;
        }

        TextDrawData missionTitleData = {
            missionTitle,
            sf::Vector2f(1225, 260),
            sf::Color(255, 255, 255),
            62,
            sf::Color(0, 0, 0),
            6,
            true
        };

        TextRenderer::drawText(window, missionTitleData);

        TextDrawData missionDescData = {
            missionDesc,
            sf::Vector2f(1225, 560),
            sf::Color(255, 255, 255),
            40,
            sf::Color(0, 0, 0),
            4,
            true
        };

        TextRenderer::drawText(window, missionDescData);

        if ((selectedMission != -1 && !MissionManager::hasAcceptedMission()) ||
            (MissionManager::missionCompleted() && selectedMission == MissionManager::getAcceptedMissionId()))
            acceptCompleteMissionButton.draw(window);

        break;
    }
    
    case StationMenuState::Level:
        stationLevelButtons.draw(window);
        break;

    }


    text = "Exit (ESC)";
    TextRenderer::drawText(window, {text, sf::Vector2f(20, 980), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3});

    window.display();

}