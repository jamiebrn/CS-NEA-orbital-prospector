#include "Game.hpp"

void Game::inStationLoop()
{

    // UI
    sf::Vector2i screenMousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = window.mapPixelToCoords(screenMousePosition);

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
                stationMenuState = StationMenuState::Main;
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


    float deltaTime = clock.restart().asSeconds();

    window.clear();

    switch (stationMenuState)
    {
    
    case StationMenuState::Main:
        inStationMainSubloop(mousePosition, leftMousePressed);
        break;
    
    case StationMenuState::Upgrades:
        inStationUpgradesSubloop(mousePosition, leftMousePressed);
        break;

    case StationMenuState::Market:
        inStationMarketSubloop(mousePosition, leftMousePressed);
        break;
    
    case StationMenuState::Missons:
        inStationMissionsSubloop(mousePosition, leftMousePressed);
        break;
    
    case StationMenuState::Level:
        inStationLevelSubloop(mousePosition, leftMousePressed);
        break;
    
    case StationMenuState::Travel:
        inStationTravelSubloop(mousePosition, leftMousePressed);
        break;

    }

    TextRenderer::drawText(window, {"Space Station", sf::Vector2f(WINDOW_WIDTH / 2, 80), sf::Color(255, 255, 255), 100, sf::Color(0, 0, 0), 4, true});

    window.display();

}


void Game::inStationMainSubloop(sf::Vector2f mousePos, bool leftMousePressed)
{
    stationMenuButtons.update(mousePos);

    if (leftMousePressed)
    {
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
        else if (stationMenuButtons.isButtonPressed("travel"))
        {
            stationMenuState = StationMenuState::Travel;    
        }
        else if (stationMenuButtons.isButtonPressed("return"))
        {
            changeState(GameState::InSpace);
        }
    }

    TextureDrawData backgroundData = {
        TextureType::SpaceStationMenuBackground,
        sf::Vector2f(0, 0),
        sf::degrees(0),
        1,
        false
    };

    TextureManager::drawTexture(window, backgroundData);

    stationMenuButtons.draw(window);
}


void Game::inStationUpgradesSubloop(sf::Vector2f mousePos, bool leftMousePressed)
{
    stationUpgradeButtons.update(mousePos);

    if (leftMousePressed)
    {
        if (stationUpgradeButtons.isButtonPressed("health"))
        {
            int health = playerShip.getMaxHealth() + 5;
            health = std::min(health, 80);
            playerShip.setMaxHealth(health);
        }
    }

    TextureDrawData backgroundData = {
        TextureType::SpaceStationSubmenuBackground,
        sf::Vector2f(0, 0),
        sf::degrees(0),
        1,
        false
    };

    TextureManager::drawTexture(window, backgroundData);

    stationUpgradeButtons.draw(window);
}


void Game::inStationMarketSubloop(sf::Vector2f mousePos, bool leftMousePressed)
{
    std::vector<UITradeItemBar> tradeItemBars;

    int yOffset = 0;
    for (std::pair<ItemPickupType, TextureType> itemTexturePair : itemTextureMap)
    {

        ItemPickupType itemType = itemTexturePair.first;

        if (InventoryManager::getItemCount(itemType) <= 0)
            continue;

        UITradeItemBar tradeItemBar;

        tradeItemBar.setTradeActionText("Sell");
        tradeItemBar.addRequiredItems(itemType, InventoryManager::getItemCount(itemType));
        tradeItemBar.setOfferCoins(InventoryManager::itemPrice(itemType) * InventoryManager::getItemCount(itemType));

        tradeItemBar.setPosition(sf::Vector2f(400, 300 + yOffset));
        tradeItemBar.update(mousePos);

        tradeItemBars.push_back(tradeItemBar);

        yOffset += tradeItemBar.getBarHeight() + 25;

    }

    if (leftMousePressed)
    {
        for (UITradeItemBar& tradeItemBar : tradeItemBars)
        {
            if (tradeItemBar.tradeButtonHovering())
                tradeItemBar.acceptTrade();
        }
    }


    TextureDrawData backgroundData = {
        TextureType::SpaceStationSubmenuBackground,
        sf::Vector2f(0, 0),
        sf::degrees(0),
        1,
        false
    };

    TextureManager::drawTexture(window, backgroundData);

    for (UITradeItemBar& tradeItemBar : tradeItemBars)
    {
        tradeItemBar.draw(window);
    }

    if (tradeItemBars.size() <= 0)
    {
        TextRenderer::drawText(window, {"You have no items to sell", sf::Vector2f(400, 500), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3, false, true});
    }

    TextureDrawData drawData = {
        TextureType::SilverCoin,
        sf::Vector2f(200, 250),
        sf::degrees(0),
        5
    };

    TextureManager::drawTexture(window, drawData);

    std::string text = std::to_string(InventoryManager::getSilverCoins());
    TextRenderer::drawText(window, {text, sf::Vector2f(240, 250), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3, false, true});

    if (InventoryManager::getItemCount(ItemPickupType::CopperChunk) > 0)
    {
        UITradeItemBar copperBarSmeltBar;

        copperBarSmeltBar.setTradeActionText("Smelt");
        copperBarSmeltBar.addRequiredItems(ItemPickupType::CopperChunk, 2);
        copperBarSmeltBar.setRequiredCoins(1);
        copperBarSmeltBar.setOfferItem(ItemPickupType::CopperBar);

        copperBarSmeltBar.setPosition(sf::Vector2f(1000, 300));
        copperBarSmeltBar.update(mousePos);

        if (leftMousePressed)
        {
            if (copperBarSmeltBar.tradeButtonHovering())
                copperBarSmeltBar.acceptTrade();
        }

        copperBarSmeltBar.draw(window);

    }

}


void Game::inStationMissionsSubloop(sf::Vector2f mousePos, bool leftMousePressed)
{
    UIButton acceptCompleteMissionButton;

    stationMissionButtons.update(mousePos);

    acceptCompleteMissionButton.setPosition(sf::Vector2f(1125, 850));
    acceptCompleteMissionButton.setSize(sf::Vector2f(200, 70));
    acceptCompleteMissionButton.setText("Accept mission");
    if (MissionManager::missionCompleted())
        acceptCompleteMissionButton.setText("Complete mission");
    acceptCompleteMissionButton.setColour(sf::Color(15, 190, 15));
    acceptCompleteMissionButton.setHoverColour(sf::Color(20, 220, 20));
    acceptCompleteMissionButton.update(mousePos);

    if (leftMousePressed)
    {
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
    }

    TextureDrawData backgroundData = {
        TextureType::SpaceStationSubmenuBackground,
        sf::Vector2f(0, 0),
        sf::degrees(0),
        1,
        false
    };

    TextureManager::drawTexture(window, backgroundData);

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
}


void Game::inStationLevelSubloop(sf::Vector2f mousePos, bool leftMousePressed)
{
    stationLevelButtons.update(mousePos);

    TextureDrawData backgroundData = {
        TextureType::SpaceStationSubmenuBackground,
        sf::Vector2f(0, 0),
        sf::degrees(0),
        1,
        false
    };

    TextureManager::drawTexture(window, backgroundData);

    stationLevelButtons.draw(window);
}

void Game::inStationTravelSubloop(sf::Vector2f mousePos, bool leftMousePressed)
{

    stationTravelButtons.update(mousePos);

    if (leftMousePressed)
    {
        static const std::unordered_map<PlanetType, std::string> planetTypeStringMap = {
            {PlanetType::Mercury, "mercury"},
            {PlanetType::Venus, "venus"},
            {PlanetType::Earth, "earth"},
            {PlanetType::Moon, "moon"},
            {PlanetType::Mars, "mars"},
            {PlanetType::Jupiter, "jupiter"},
            {PlanetType::Saturn, "saturn"},
            {PlanetType::Uranus, "uranus"},
            {PlanetType::Neptune, "neptune"},
        };

        for (std::pair<PlanetType, std::string> planetTypeStringPair : planetTypeStringMap)
        {
            if (stationTravelButtons.isButtonPressed(planetTypeStringPair.second))
                travelToPlanet(planetTypeStringPair.first);
        }
    }

    TextureDrawData backgroundData = {
        TextureType::SpaceStationSubmenuBackground,
        sf::Vector2f(0, 0),
        sf::degrees(0),
        1,
        false
    };

    TextureManager::drawTexture(window, backgroundData);

    stationTravelButtons.draw(window);

}
