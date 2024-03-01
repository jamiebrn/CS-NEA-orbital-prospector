// GameInStation.cpp

#include "Game.hpp"

// Game loop for in space station game state
void Game::inStationLoop(float deltaTime)
{
    // Get mouse position
    sf::Vector2i screenMousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = window.mapPixelToCoords(screenMousePosition);

    // Set left mouse pressed to false by default
    bool leftMousePressed = false;

    // Check for input events
    sf::Event event;
    while (window.pollEvent(event))
    {
        // If input event is window close, close window
        if (event.type == sf::Event::Closed)
            window.close();
        
        // If input event is key press, and key is escape, set space station UI
        // state to main (provides a "back" button)
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                stationMenuState = StationMenuState::Main;
            }
        }

        // If input event is mouse wheel scroll, add to ui scroll amount
        // depending on direction of scroll
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            uiScrollCount = std::max(uiScrollCount - event.mouseWheelScroll.delta, 0.0f);
        }

        // If input event is mouse button press, and button is left mouse button,
        // set left mouse pressed variable to true
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                leftMousePressed = true;
            }
        }

    }

    // Clear window
    window.clear();

    // Switch update loop depending on the current space station UI state
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

    // Draw space station title text
    TextRenderer::drawText(window, {"Space Station", sf::Vector2f(WINDOW_WIDTH / 2, 10), sf::Color(255, 255, 255), 100, sf::Color(0, 0, 0), 4, true});

}

// Space station main update loop
void Game::inStationMainSubloop(sf::Vector2f mousePos, bool leftMousePressed)
{
    // Update space station main menu buttons
    stationMenuButtons.update(mousePos);

    // If left mouse button pressed, test for button presses
    if (leftMousePressed)
    {
        // If upgrades button is pressed, reset UI scroll amount,
        // as upgrades state uses UI scroll, and switch to space station upgrade state
        if (stationMenuButtons.isButtonPressed("upgrades"))
        {
            uiScrollCount = 0;
            stationMenuState = StationMenuState::Upgrades;
        }
        // If market button is pressed, reset UI scroll amount,
        // as market state uses UI scroll, and switch to space station market state
        else if (stationMenuButtons.isButtonPressed("market"))
        {
            uiScrollCount = 0;
            stationMenuState = StationMenuState::Market;
        }
        // If forge button is pressed, reset UI scroll amount,
        // as forge state uses UI scroll, and switch to space station forge state
        else if (stationMenuButtons.isButtonPressed("forge"))
        {
            uiScrollCount = 0;
            stationMenuState = StationMenuState::Forge;
        }
        // If missions button is pressed, switch to mission state
        else if (stationMenuButtons.isButtonPressed("missions"))
        {
            // Reset selected mission variable to -1, meaning no mission selected
            selectedMission = -1;

            // Update mission buttons with current mission data
            for (int i = 0; i < 3; i++)
            {
                std::string title = MissionManager::getMissionData(i).title;
                stationMissionButtons.setButtonText("mission" + std::to_string(i + 1), title);
            }

            // Switch state to space station missions state
            stationMenuState = StationMenuState::Missons;
        }
        // If level button is pressed, switch to level state
        else if (stationMenuButtons.isButtonPressed("level"))
        {
            stationMenuState = StationMenuState::Level;
        }
        // If travel button is pressed, switch to travel state
        else if (stationMenuButtons.isButtonPressed("travel"))
        {
            // Update selection of planets which can be travelled to,
            // depending on upgrades unlocked
            updatePlanetSelection();
            // Switch to travel state
            stationMenuState = StationMenuState::Travel;    
        }
        // If return button is pressed, leave space station (return to in space state)
        else if (stationMenuButtons.isButtonPressed("return"))
        {
            targetGameState = GameState::InSpace;
        }
    }

    // Draw background
    TextureDrawData backgroundData = {
        TextureType::SpaceStationMenuBackground,
        sf::Vector2f(0, 0),
        sf::degrees(0),
        1,
        false
    };

    TextureManager::drawTexture(window, backgroundData);

    // Draw buttons
    stationMenuButtons.draw(window);
}

// Space station upgrades update loop
void Game::inStationUpgradesSubloop(sf::Vector2f mousePos, bool leftMousePressed)
{
    // Update space station upgrade buttons
    stationUpgradeButtons.update(mousePos);

    // Create vector containing UI trade bar elements, containing
    // all possible upgrades
    std::vector<UITradeItemBar> upgradeBars;

    // Keep track of y position of UI elements
    int yOffset = 0;
    // Keep track of how many upgrades are available
    int itemCount = 0;
    // Iterate over all upgrade recipes, checking it the player can
    // afford to unlock the upgrade, and adding a UI trade bar element
    // to the vector if so
    for (Recipes::UpgradeData upgradeData : Recipes::upgrades)
    {
        // If player already has upgrade, do not add it to unlockable upgrades
        if (UpgradeManager::hasUpgrade(upgradeData.upgrade))
            continue;
        
        // If upgrade has a prerequisite upgrade, and the player does not have
        // this prerequisite upgrade, do not add it to unlockable upgrades
        if (!UpgradeManager::hasUpgrade(upgradeData.prerequisiteUpgrade))
            continue;
        
        // Create UI trade item bar object
        UITradeItemBar upgradeBar;

        // Change the UI trade bar trade button text to "Upgrade"
        upgradeBar.setTradeActionText("Upgrade");
        // Set the sound effect to be played when the upgrade is unlocked
        upgradeBar.setTradeActionSound(SoundType::Forge);

        // If the upgrade requires more coins than the player has, do not
        // offer this upgrade to the player
        if (upgradeData.requiredCoins > InventoryManager::getSilverCoins())
            continue;
        
        // Set the upgrade bar required coins and offered upgrade
        upgradeBar.setRequiredCoins(upgradeData.requiredCoins);
        upgradeBar.setOfferUpgrade(upgradeData.upgrade);

        // Keep track of whether the player has all required items - true by default
        bool hasRequiredItems = true;
        // Iterate over all items required for the upgrade and check if the player has them,
        // while adding them as a requirement to the upgrade bar
        for (std::pair<ItemPickupType, int> itemCount : upgradeData.requiredItems)
        {
            // Add items to upgrade bar
            upgradeBar.addRequiredItems(itemCount.first, itemCount.second);

            // If player does not have items, set has required items to false and stop checking
            // required items
            if (InventoryManager::getItemCount(itemCount.first) < itemCount.second)
            {
                hasRequiredItems = false;
                break;
            }
        }

        // If player does not have required items, do not offer upgrade
        if (!hasRequiredItems)
            continue;
        
        // Increment amount of upgrades offered to player, as at this point
        // it has been determined that the player can unlock this upgrade
        itemCount++;
        // If the current amount of upgrades unlocked is smaller than the scroll
        // amount, do not offer it, as the player has scrolled past it, so should
        // not be drawn
        if (itemCount < uiScrollCount)
            continue;
        
        // Set position of upgrade bar and update it
        upgradeBar.setPosition(sf::Vector2f(400, 300 + yOffset));
        upgradeBar.update(mousePos);

        // Add upgrade bar to vector
        upgradeBars.push_back(upgradeBar);

        // Increment y offset
        yOffset += upgradeBar.getBarHeight() + 25;
    }

    // If left mouse pressed, check for button press on all upgrade bars
    if (leftMousePressed)
    {
        for (UITradeItemBar& upgradeBar : upgradeBars)
        {
            // If trade (upgrade) button is pressed, accept trade
            if (upgradeBar.tradeButtonHovering())
                upgradeBar.acceptTrade();
        }
    }

    // Draw background
    TextureDrawData backgroundData = {
        TextureType::SpaceStationSubmenuBackground,
        sf::Vector2f(0, 0),
        sf::degrees(0),
        1,
        false
    };

    TextureManager::drawTexture(window, backgroundData);

    // Draw upgrade bars
    for (UITradeItemBar& upgradeBar : upgradeBars)
    {
        upgradeBar.draw(window);
    }

    // If no upgrades are available, tell player
    if (itemCount <= 0)
    {
        TextRenderer::drawText(window, {"No upgrades available", sf::Vector2f(400, 500), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3, false, true});
    }

    // Draw coin symbol
    TextureDrawData drawData = {
        TextureType::SilverCoin,
        sf::Vector2f(200, 250),
        sf::degrees(0),
        5
    };

    TextureManager::drawTexture(window, drawData);

    // Draw amount of coins player has
    std::string text = std::to_string(InventoryManager::getSilverCoins());
    TextRenderer::drawText(window, {text, sf::Vector2f(240, 250), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3, false, true});
}

// Space station market update loop
void Game::inStationMarketSubloop(sf::Vector2f mousePos, bool leftMousePressed)
{
    // Update space station market buttons
    stationMarketButtons.update(mousePos);

    // If left mouse if pressed, check for button presses
    if (leftMousePressed)
    {
        // Change amount of item to sell when a button is pressed
        if (stationMarketButtons.isButtonPressed("sell1")) stationMarketButtons.generalData["sellAmount"] = 0;
        else if (stationMarketButtons.isButtonPressed("sell25%")) stationMarketButtons.generalData["sellAmount"] = 25;
        else if (stationMarketButtons.isButtonPressed("sell50%")) stationMarketButtons.generalData["sellAmount"] = 50;
        else if (stationMarketButtons.isButtonPressed("sell75%")) stationMarketButtons.generalData["sellAmount"] = 75;
        else if (stationMarketButtons.isButtonPressed("sell100%")) stationMarketButtons.generalData["sellAmount"] = 100;
    }

    // Vector containing UI trade item bars (to sell items)
    std::vector<UITradeItemBar> tradeItemBars;

    // Keep track of y offset of UI elements
    int yOffset = 0;
    // Keep track of amount of different items available to sell
    int itemCount = 0;
    // Iterate over all item types and test if player has any to sell
    for (std::pair<ItemPickupType, TextureType> itemTexturePair : itemTextureMap)
    {
        // Get item type from map
        ItemPickupType itemType = itemTexturePair.first;

        // If player has none of this item, do not create UI element for them to
        // sell it
        if (InventoryManager::getItemCount(itemType) <= 0)
            continue;
        
        // Increment item count, as player can sell this item
        itemCount++;
        // If item count is smaller than scroll count, do not add this UI element
        // to vector, as player has scrolled past it so should not be drawn
        if (itemCount < uiScrollCount)
            continue;
        
        // Create UI trade item bar
        UITradeItemBar tradeItemBar;

        // Set trade button text to "Sell"
        tradeItemBar.setTradeActionText("Sell");
        // Set trade action sound
        tradeItemBar.setTradeActionSound(SoundType::Coins);

        // Get amount of items to sell based on amount of item player has and
        // percentage of items to sell
        int itemCount = std::max(1, static_cast<int>(InventoryManager::getItemCount(itemType) * (static_cast<float>(stationMarketButtons.generalData["sellAmount"]) / 100)));
        if (stationMarketButtons.generalData["sellAmount"] == 0) itemCount = 1;

        // Add item as a requirement for trade
        tradeItemBar.addRequiredItems(itemType, itemCount);
        // Set amount of coins item will sell for
        tradeItemBar.setOfferCoins(InventoryManager::itemPrice(itemType) * itemCount);

        // Set position of trade item bar and update it
        tradeItemBar.setPosition(sf::Vector2f(400, 300 + yOffset));
        tradeItemBar.update(mousePos);

        // Add trade item bar to vector
        tradeItemBars.push_back(tradeItemBar);

        // Add to y offset
        yOffset += tradeItemBar.getBarHeight() + 25;
    }

    // If left mouse is pressed, check for trade button presses
    if (leftMousePressed)
    {
        for (UITradeItemBar& tradeItemBar : tradeItemBars)
        {
            // If button is pressed, accept trade
            if (tradeItemBar.tradeButtonHovering())
                tradeItemBar.acceptTrade();
        }
    }

    // Draw background
    TextureDrawData backgroundData = {
        TextureType::SpaceStationSubmenuBackground,
        sf::Vector2f(0, 0),
        sf::degrees(0),
        1,
        false
    };

    TextureManager::drawTexture(window, backgroundData);

    // Draw buttons
    stationMarketButtons.draw(window);

    // Draw trade item bars
    for (UITradeItemBar& tradeItemBar : tradeItemBars)
    {
        tradeItemBar.draw(window);
    }

    // If player has no items to sell, tell them
    if (itemCount <= 0)
    {
        TextRenderer::drawText(window, {"You have no items to sell", sf::Vector2f(400, 500), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3, false, true});
    }

    // Draw coin symbol
    TextureDrawData drawData = {
        TextureType::SilverCoin,
        sf::Vector2f(200, 250),
        sf::degrees(0),
        5
    };

    TextureManager::drawTexture(window, drawData);

    // Draw player's coin quantity
    std::string text = std::to_string(InventoryManager::getSilverCoins());
    TextRenderer::drawText(window, {text, sf::Vector2f(240, 250), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3, false, true});
}

// Space station forge update loop
void Game::inStationForgeSubloop(sf::Vector2f mousePos, bool leftMousePressed)
{
    // Vector of UI trade item bars for smelting items
    std::vector<UITradeItemBar> smeltItemBars;

    // Keep track of y offset of UI elements
    int yOffset = 0;
    // Keep track of how many trade item bars are made
    int itemCount = 0;
    // Iterate over all smelting recipes and test if player has required items
    for (Recipes::SmeltData smeltData : Recipes::smelting)
    {
        // Create trade item bar
        UITradeItemBar smeltItemBar;

        // Set trade button text to "Smelt"
        smeltItemBar.setTradeActionText("Smelt");
        // Set trade action sound
        smeltItemBar.setTradeActionSound(SoundType::Forge);

        // If player does not have required coins, do not add trade item bar to vector
        if (smeltData.requiredCoins > InventoryManager::getSilverCoins())
            continue;
        
        // Set required coins and product of smelting
        smeltItemBar.setRequiredCoins(smeltData.requiredCoins);
        smeltItemBar.setOfferItem(smeltData.product);

        // Test whether player has required items
        bool hasRequiredItems = true;
        for (std::pair<ItemPickupType, int> itemCount : smeltData.requiredItems)
        {
            // Add required items to trade item bar
            smeltItemBar.addRequiredItems(itemCount.first, itemCount.second);

            // If player does not have enough of item, set has required items to false and stop checking
            // whether player has all items
            if (InventoryManager::getItemCount(itemCount.first) < itemCount.second)
            {
                hasRequiredItems = false;
                break;
            }
        }

        // If player does not have required items, do not add trade item bar to vector
        if (!hasRequiredItems)
            continue;
        
        // Increment item count, as player can make this recipe
        itemCount++;
        // If item count if smaller than scroll count, do not add trade item bar to
        // vector, as player has scrolled past it, so should not be drawn
        if (itemCount < uiScrollCount)
            continue;
        
        // Set position of trade item bar and update
        smeltItemBar.setPosition(sf::Vector2f(400, 300 + yOffset));
        smeltItemBar.update(mousePos);

        // Add trade item bar to vector
        smeltItemBars.push_back(smeltItemBar);

        // Increment y offset
        yOffset += smeltItemBar.getBarHeight() + 25;
    }

    // If left mouse button is pressed, check for trade button presses
    if (leftMousePressed)
    {
        for (UITradeItemBar& smeltItemBar : smeltItemBars)
        {
            // If trade button is pressed, accept trade
            if (smeltItemBar.tradeButtonHovering())
                smeltItemBar.acceptTrade();
        }
    }

    // Draw background
    TextureDrawData backgroundData = {
        TextureType::SpaceStationSubmenuBackground,
        sf::Vector2f(0, 0),
        sf::degrees(0),
        1,
        false
    };

    TextureManager::drawTexture(window, backgroundData);

    // Draw trade (smelt) item bars
    for (UITradeItemBar& smeltItemBar : smeltItemBars)
    {
        smeltItemBar.draw(window);
    }

    // If player cannot smelt/forge any items, tell them
    if (itemCount <= 0)
    {
        TextRenderer::drawText(window, {"No items are available to be forged", sf::Vector2f(400, 500), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3, false, true});
    }

    // Draw coin symbol
    TextureDrawData drawData = {
        TextureType::SilverCoin,
        sf::Vector2f(200, 250),
        sf::degrees(0),
        5
    };

    TextureManager::drawTexture(window, drawData);

    // Draw player's coin quantity
    std::string text = std::to_string(InventoryManager::getSilverCoins());
    TextRenderer::drawText(window, {text, sf::Vector2f(240, 250), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3, false, true});
}

// Space station missions update loop
void Game::inStationMissionsSubloop(sf::Vector2f mousePos, bool leftMousePressed)
{
    // Create button for accepting/completing missions (depending on requirements)
    UIButton acceptCompleteMissionButton;

    // Update space station mission state buttons
    stationMissionButtons.update(mousePos);

    // Set data of accept/complete mission button
    acceptCompleteMissionButton.setPosition(sf::Vector2f(1125, 850));
    acceptCompleteMissionButton.setSize(sf::Vector2f(200, 70));
    acceptCompleteMissionButton.setText("Accept mission");

    // If a mission has been completed, set the text to "Complete mission"
    if (MissionManager::missionCompleted())
        acceptCompleteMissionButton.setText("Complete mission");
    
    // Set data of accept/complete mission button and update
    acceptCompleteMissionButton.setColour(sf::Color(15, 190, 15));
    acceptCompleteMissionButton.setHoverColour(sf::Color(20, 220, 20));
    acceptCompleteMissionButton.update(mousePos);

    // If left mouse button is pressed, check for any button presses
    if (leftMousePressed)
    {
        // Check all mission buttons, and if pressed, set selected mission
        for (int i = 0; i < 3; i++)
        {
            if (stationMissionButtons.isButtonPressed("mission" + std::to_string(i + 1)))
            {
                selectedMission = i;
            }
        }

        // If accept mission button is clicked, and no mission has been accepted, accept the selected mission
        if (acceptCompleteMissionButton.isHovering() && !MissionManager::hasAcceptedMission())
        {
            if (selectedMission != -1)
            {
                MissionManager::acceptMission(selectedMission);
            }
        }
        // If accept/complete mission button is clicked, and a mission has been completed, complete the mission
        if (acceptCompleteMissionButton.isHovering() && MissionManager::missionCompleted())
        {
            // Complete mission
            MissionManager::completeMission();

            // Update all mission buttons to read new mission data
            for (int i = 0; i < 3; i++)
            {
                std::string title = MissionManager::getMissionData(i).title;
                stationMissionButtons.setButtonText("mission" + std::to_string(i + 1), title);
            }

            // Reset selected mission to none
            selectedMission = -1;
        }
    }

    // Draw background
    TextureDrawData backgroundData = {
        TextureType::SpaceStationSubmenuBackground,
        sf::Vector2f(0, 0),
        sf::degrees(0),
        1,
        false
    };

    TextureManager::drawTexture(window, backgroundData);

    // Draw mission buttons
    stationMissionButtons.draw(window);

    // Draw border background
    sf::RectangleShape missionBg(sf::Vector2f(1260, 800));
    missionBg.setPosition(sf::Vector2f(595, 220));
    missionBg.setFillColor(sf::Color(40, 40, 40, 130));
    window.draw(missionBg);

    // Draw mission titles
    std::string missionTitle = "Mission Info";
    std::string missionDesc = "Select mission for more info";
    // If a mission is selected, set mission data to the mission data
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

    // If a mission is selected and a mission is not in progress,
    // or the currently selected mission has been completed, draw the
    // accept/complete mission button
    if ((selectedMission != -1 && !MissionManager::hasAcceptedMission()) ||
        (MissionManager::missionCompleted() && selectedMission == MissionManager::getAcceptedMissionId()))
        acceptCompleteMissionButton.draw(window);
}

// Space station level update loop
void Game::inStationLevelSubloop(sf::Vector2f mousePos, bool leftMousePressed)
{
    // Update level buttons
    stationLevelButtons.update(mousePos);

    // Draw background
    TextureDrawData backgroundData = {
        TextureType::SpaceStationSubmenuBackground,
        sf::Vector2f(0, 0),
        sf::degrees(0),
        1,
        false
    };

    TextureManager::drawTexture(window, backgroundData);

    // Draw level buttons
    stationLevelButtons.draw(window);
}

// Space station travel update loop
void Game::inStationTravelSubloop(sf::Vector2f mousePos, bool leftMousePressed)
{
    // Update travel buttons
    stationTravelButtons.update(mousePos);

    // If left mouse pressed, check for button presses
    if (leftMousePressed)
    {
        // Check all buttons in travel buttons
        for (auto buttonPair : stationTravelButtons.getButtonMap())
        {
            // Get name of destination planet
            std::string planetName = buttonPair.first;

            // If this travel button is pressed, travel to this planet
            if (stationTravelButtons.isButtonPressed(planetName))
                travelToPlanet(planetTravelDataMap.at(planetName).planetType);
        }
    }

    // Draw background
    TextureDrawData backgroundData = {
        TextureType::SpaceStationSubmenuBackground,
        sf::Vector2f(0, 0),
        sf::degrees(0),
        1,
        false
    };

    TextureManager::drawTexture(window, backgroundData);

    // If no travel buttons, tell player they cannot travel anywhere
    if (stationTravelButtons.getButtonMap().size() <= 0)
    {
        TextRenderer::drawText(window, {"You do not have the technology to travel", sf::Vector2f(400, 500), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3, false, true});
    }

    // Draw travel buttons
    stationTravelButtons.draw(window);
}

// Used to update the selection of planets the player can travel to
// by using the space station UI
void Game::updatePlanetSelection()
{
    // Delete all travel buttons
    stationTravelButtons.clear();

    // Set initial button y offset
    int yOffset = 200;

    // Iterate over all possible destinations and check requirements
    for (auto planetTravelDataPair : planetTravelDataMap)
    {
        // Get travel data from map
        PlanetTravelData travelData = planetTravelDataPair.second;

        // If the destination is the current planet, do not add to travel destinations
        if (travelData.planetType == currentPlanet)
            continue;
        
        // If player does not have required upgrade, do not add to travel destinations
        if (!UpgradeManager::hasUpgrade(travelData.requiredUpgrade))
            continue;
        
        // If player is not at the prerequisite planet, do not add to travel destinations
        if (travelData.prerequisitePlanet != PlanetType::NONE && currentPlanet != travelData.prerequisitePlanet)
            continue;
        
        // Get planet name from travel data
        std::string planetName = planetTravelDataPair.first;

        // Add travel button for planet
        stationTravelButtons.addButton(planetName, {
            sf::Vector2f(300, yOffset), sf::Vector2f(700, 100),
            planetName, sf::Color(15, 190, 15), sf::Color(20, 220, 20)
        });

        // Increment y offset
        yOffset += 110;
    }

}