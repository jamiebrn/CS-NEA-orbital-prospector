#include "Game.hpp"

void Game::inStationLoop(float deltaTime)
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

        if (event.type == sf::Event::MouseWheelScrolled)
        {
            uiScrollCount = std::max(uiScrollCount - event.mouseWheelScroll.delta, 0.0f);
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                leftMousePressed = true;
            }
        }

    }

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
    
    case StationMenuState::Forge:
        inStationForgeSubloop(mousePosition, leftMousePressed);
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

    TextRenderer::drawText(window, {"Space Station", sf::Vector2f(WINDOW_WIDTH / 2, 10), sf::Color(255, 255, 255), 100, sf::Color(0, 0, 0), 4, true});

}


void Game::inStationMainSubloop(sf::Vector2f mousePos, bool leftMousePressed)
{
    stationMenuButtons.update(mousePos);

    if (leftMousePressed)
    {
        if (stationMenuButtons.isButtonPressed("upgrades"))
        {
            uiScrollCount = 0;
            stationMenuState = StationMenuState::Upgrades;
        }
        else if (stationMenuButtons.isButtonPressed("market"))
        {
            uiScrollCount = 0;
            stationMenuState = StationMenuState::Market;
        }
        else if (stationMenuButtons.isButtonPressed("forge"))
        {
            uiScrollCount = 0;
            stationMenuState = StationMenuState::Forge;
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
            updatePlanetSelection();
            stationMenuState = StationMenuState::Travel;    
        }
        else if (stationMenuButtons.isButtonPressed("return"))
        {
            targetGameState = GameState::InSpace;
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

    std::vector<UITradeItemBar> upgradeBars;

    int yOffset = 0;
    int itemCount = 0;
    for (Recipes::UpgradeData upgradeData : Recipes::upgrades)
    {

        if (UpgradeManager::hasUpgrade(upgradeData.upgrade))
            continue;
        
        if (upgradeData.prerequisiteUpgrade != UpgradeType::NONE && !UpgradeManager::hasUpgrade(upgradeData.prerequisiteUpgrade))
            continue;

        UITradeItemBar upgradeBar;
        upgradeBar.setTradeActionText("Upgrade");
        upgradeBar.setTradeActionSound(SoundType::Forge);

        if (upgradeData.requiredCoins > InventoryManager::getSilverCoins())
            continue;

        upgradeBar.setRequiredCoins(upgradeData.requiredCoins);
        upgradeBar.setOfferUpgrade(upgradeData.upgrade);

        bool hasRequiredItems = true;
        for (std::pair<ItemPickupType, int> itemCount : upgradeData.requiredItems)
        {
            upgradeBar.addRequiredItems(itemCount.first, itemCount.second);

            if (InventoryManager::getItemCount(itemCount.first) < itemCount.second)
            {
                hasRequiredItems = false;
                break;
            }
        }

        if (!hasRequiredItems)
            continue;
        
        itemCount++;
        if (itemCount < uiScrollCount)
            continue;

        upgradeBar.setPosition(sf::Vector2f(400, 300 + yOffset));
        upgradeBar.update(mousePos);

        upgradeBars.push_back(upgradeBar);

        yOffset += upgradeBar.getBarHeight() + 25;

    }

    if (leftMousePressed)
    {
        for (UITradeItemBar& upgradeBar : upgradeBars)
        {
            if (upgradeBar.tradeButtonHovering())
                upgradeBar.acceptTrade();
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

    for (UITradeItemBar& upgradeBar : upgradeBars)
    {
        upgradeBar.draw(window);
    }

    if (itemCount <= 0)
    {
        TextRenderer::drawText(window, {"No upgrades available", sf::Vector2f(400, 500), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3, false, true});
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
}


void Game::inStationMarketSubloop(sf::Vector2f mousePos, bool leftMousePressed)
{

    stationMarketButtons.update(mousePos);

    if (leftMousePressed)
    {
        if (stationMarketButtons.isButtonPressed("sell1")) stationMarketButtons.generalData["sellAmount"] = 0;
        else if (stationMarketButtons.isButtonPressed("sell25%")) stationMarketButtons.generalData["sellAmount"] = 25;
        else if (stationMarketButtons.isButtonPressed("sell50%")) stationMarketButtons.generalData["sellAmount"] = 50;
        else if (stationMarketButtons.isButtonPressed("sell75%")) stationMarketButtons.generalData["sellAmount"] = 75;
        else if (stationMarketButtons.isButtonPressed("sell100%")) stationMarketButtons.generalData["sellAmount"] = 100;
    }

    std::vector<UITradeItemBar> tradeItemBars;

    int yOffset = 0;
    int itemCount = 0;
    for (std::pair<ItemPickupType, TextureType> itemTexturePair : itemTextureMap)
    {

        ItemPickupType itemType = itemTexturePair.first;

        if (InventoryManager::getItemCount(itemType) <= 0)
            continue;
        
        itemCount++;
        if (itemCount < uiScrollCount)
            continue;
        
        UITradeItemBar tradeItemBar;

        tradeItemBar.setTradeActionText("Sell");
        tradeItemBar.setTradeActionSound(SoundType::Coins);

        int itemCount = std::max(1, static_cast<int>(InventoryManager::getItemCount(itemType) * (static_cast<float>(stationMarketButtons.generalData["sellAmount"]) / 100)));
        if (stationMarketButtons.generalData["sellAmount"] == 0) itemCount = 1;

        tradeItemBar.addRequiredItems(itemType, itemCount);
        tradeItemBar.setOfferCoins(InventoryManager::itemPrice(itemType) * itemCount);

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

    stationMarketButtons.draw(window);

    for (UITradeItemBar& tradeItemBar : tradeItemBars)
    {
        tradeItemBar.draw(window);
    }

    if (itemCount <= 0)
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

}

void Game::inStationForgeSubloop(sf::Vector2f mousePos, bool leftMousePressed)
{

    std::vector<UITradeItemBar> smeltItemBars;

    int yOffset = 0;
    int itemCount = 0;
    for (Recipes::SmeltData smeltData : Recipes::smelting)
    {

        UITradeItemBar smeltItemBar;
        smeltItemBar.setTradeActionText("Smelt");
        smeltItemBar.setTradeActionSound(SoundType::Forge);

        if (smeltData.requiredCoins > InventoryManager::getSilverCoins())
            continue;

        smeltItemBar.setRequiredCoins(smeltData.requiredCoins);
        smeltItemBar.setOfferItem(smeltData.product);

        bool hasRequiredItems = true;
        for (std::pair<ItemPickupType, int> itemCount : smeltData.requiredItems)
        {
            smeltItemBar.addRequiredItems(itemCount.first, itemCount.second);

            if (InventoryManager::getItemCount(itemCount.first) < itemCount.second)
            {
                hasRequiredItems = false;
                break;
            }
        }

        if (!hasRequiredItems)
            continue;
        
        itemCount++;
        if (itemCount < uiScrollCount)
            continue;

        smeltItemBar.setPosition(sf::Vector2f(400, 300 + yOffset));
        smeltItemBar.update(mousePos);

        smeltItemBars.push_back(smeltItemBar);

        yOffset += smeltItemBar.getBarHeight() + 25;

    }

    if (leftMousePressed)
    {
        for (UITradeItemBar& smeltItemBar : smeltItemBars)
        {
            if (smeltItemBar.tradeButtonHovering())
                smeltItemBar.acceptTrade();
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

    for (UITradeItemBar& smeltItemBar : smeltItemBars)
    {
        smeltItemBar.draw(window);
    }

    if (itemCount <= 0)
    {
        TextRenderer::drawText(window, {"No items are available to be forged", sf::Vector2f(400, 500), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3, false, true});
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

        for (auto buttonPair : stationTravelButtons.getButtonMap())
        {
            std::string planetName = buttonPair.first;

            if (stationTravelButtons.isButtonPressed(planetName))
                travelToPlanet(planetTravelDataMap.at(planetName).planetType);
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

    if (stationTravelButtons.getButtonMap().size() <= 0)
    {
        TextRenderer::drawText(window, {"You do not have the technology to travel", sf::Vector2f(400, 500), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3, false, true});
    }

    stationTravelButtons.draw(window);

}

void Game::updatePlanetSelection()
{

    stationTravelButtons.clear();
    
    int yOffset = 200;

    // Space station travel buttons
    
    for (auto planetTravelDataPair : planetTravelDataMap)
    {

        PlanetTravelData travelData = planetTravelDataPair.second;

        if (travelData.planetType == currentPlanet)
            continue;

        if (!UpgradeManager::hasUpgrade(travelData.requiredUpgrade))
            continue;
        
        if (travelData.prerequisitePlanet != PlanetType::NONE && currentPlanet != travelData.prerequisitePlanet)
            continue;
        
        std::string planetName = planetTravelDataPair.first;

        stationTravelButtons.addButton(planetName, {
            sf::Vector2f(300, yOffset), sf::Vector2f(700, 100),
            planetName, sf::Color(15, 190, 15), sf::Color(20, 220, 20)
        });

        yOffset += 110;
        
    }

}