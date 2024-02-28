// UITradeItemBar.cpp

#include "UI/UITradeItemBar.hpp"

// Constructor
UITradeItemBar::UITradeItemBar()
{
    // Initialise trade requirements to 0
    requiredItems.clear();
    requiredCoins = 0;

    // Initialise trade offer to 0
    offerItem = ItemPickupType::NONE;
    offerUpgrade = UpgradeType::NONE;
    offerCoins = 0;

    // Initialise trade sound to not contain any sound
    tradeSound.reset();

    // Initialise trade button to default "trade" settings
    tradeButton.setText("Trade");
    tradeButton.setSize(sf::Vector2f(150, 75));
    tradeButton.setColour(sf::Color(20, 190, 20));
    tradeButton.setHoverColour(sf::Color(30, 200, 30));
    
}

// Add items that player needs to perform trade
void UITradeItemBar::addRequiredItems(ItemPickupType itemType, int amount)
{
    requiredItems[itemType] = amount;
}

// Set amount of coins that player needs to perform trade
void UITradeItemBar::setRequiredCoins(int amount)
{
    requiredCoins = amount;
}

// Set item that player is offered
void UITradeItemBar::setOfferItem(ItemPickupType itemType)
{
    offerItem = itemType;
}

// Set coins that player is offered
void UITradeItemBar::setOfferCoins(int amount)
{
    offerCoins = amount;
}

// Set upgrade that player is offered
void UITradeItemBar::setOfferUpgrade(UpgradeType upgrade)
{
    offerUpgrade = upgrade;
}

// Set text that is drawn on button which performs trade action
void UITradeItemBar::setTradeActionText(std::string text)
{
    tradeButton.setText(text);
}

// Set sound effect that plays when trade is performed
void UITradeItemBar::setTradeActionSound(SoundType type)
{
    tradeSound.emplace(type);
}

// Set position of trade bar UI element
void UITradeItemBar::setPosition(sf::Vector2f position)
{
    this->position = position;
    // Set position of trade button
    tradeButton.setPosition(position + sf::Vector2f(610, 12));
}

// Update using mouse position, for trade button
void UITradeItemBar::update(sf::Vector2f mousePos)
{
    tradeButton.update(mousePos);
}

// Returns whether the trade button is being hovered over
bool UITradeItemBar::tradeButtonHovering()
{
    return tradeButton.isHovering();
}

// Accept trade
void UITradeItemBar::acceptTrade()
{
    // Take all required items from inventory
    for (std::pair<ItemPickupType, int> itemPair : requiredItems)
    {
        InventoryManager::addItem(itemPair.first, -itemPair.second);
    }

    // Take required silver coins
    InventoryManager::addSilverCoins(-requiredCoins);

    // If an item if being offered, give the item
    if (offerItem != ItemPickupType::NONE)
        InventoryManager::addItem(offerItem, 1);
    
    // If an upgrade is being offered, unlock the upgrade
    if (offerUpgrade != UpgradeType::NONE)
        UpgradeManager::unlockUpgrade(offerUpgrade);
    
    // If coins are being offered, give the coins
    InventoryManager::addSilverCoins(offerCoins);

    // If a sound should be played when trade performed, play it
    if (tradeSound.has_value())
        SoundManager::playSound(tradeSound.value());
}

// Draw trade bar UI element
void UITradeItemBar::draw(sf::RenderWindow& window)
{
    // Create rectangle for background of trade bar UI element
    sf::RectangleShape background(sf::Vector2f(800, getBarHeight()));
    background.setPosition(position);
    background.setFillColor(sf::Color(20, 20, 20, 100));

    // Draw background rectangle
    window.draw(background);

    // If an item is being offered, draw it
    if (offerItem != ItemPickupType::NONE)
    {
        // Create item draw data
        TextureDrawData drawData = {
            itemTextureMap.at(offerItem),
            position + sf::Vector2f(50, 50),
            sf::degrees(0),
            5
        };

        // Draw item
        TextureManager::drawTexture(window, drawData);
    }

    // If an upgrade is being offered, draw it
    if (offerUpgrade != UpgradeType::NONE)
    {
        // Create upgrade draw data
        TextureDrawData drawData = {
            upgradeTextureMap.at(offerUpgrade),
            position + sf::Vector2f(50, 50),
            sf::degrees(0),
            5
        };

        // Draw upgrade
        TextureManager::drawTexture(window, drawData);
    }

    // If coins are being offered, draw coin symbol and quantity
    if (offerCoins > 0)
    {
        // Create coin symbol draw data
        TextureDrawData drawData = {
            TextureType::SilverCoin,
            position + sf::Vector2f(50, 50),
            sf::degrees(0),
            5
        };

        // Draw coin symbol
        TextureManager::drawTexture(window, drawData);

        // Create coin quantity draw data
        TextDrawData quantityLabel = {
            std::to_string(offerCoins),
            position + sf::Vector2f(90, 50),
            sf::Color(255, 255, 255),
            40,
            sf::Color(0, 0, 0),
            3,
            false,
            true
        };

        // Draw coin quantity text
        TextRenderer::drawText(window, quantityLabel);
    }

    // Keep track of where to place required items on the trade bar
    int requiredItemYOffset = 50;

    // Iterate over all required items and draw them
    for (std::pair<ItemPickupType, int> item : requiredItems)
    {
        // Create draw data for item
        TextureDrawData drawData = {
            itemTextureMap.at(item.first),
            position + sf::Vector2f(300, requiredItemYOffset),
            sf::degrees(0),
            5
        };

        // Draw item
        TextureManager::drawTexture(window, drawData);

        // Create draw data for quantity of item text
        TextDrawData quantityLabel = {
            std::to_string(item.second) + "/" + std::to_string(InventoryManager::getItemCount(item.first)),
            position + sf::Vector2f(340, requiredItemYOffset),
            sf::Color(255, 255, 255),
            40,
            sf::Color(0, 0, 0),
            3,
            false,
            true
        };

        // Draw text displaying quantity of item required
        TextRenderer::drawText(window, quantityLabel);

        // Increment position for where required items should be drawn
        requiredItemYOffset += 100;
    }

    // If coins are required, draw coin symbol and quantity
    if (requiredCoins > 0)
    {
        // Create coin symbol draw data
        TextureDrawData drawData = {
            TextureType::SilverCoin,
            position + sf::Vector2f(300, requiredItemYOffset),
            sf::degrees(0),
            5
        };

        // Draw coin symbol
        TextureManager::drawTexture(window, drawData);

        // Create coin quantity draw data
        TextDrawData quantityLabel = {
            std::to_string(requiredCoins),
            position + sf::Vector2f(340, requiredItemYOffset),
            sf::Color(255, 255, 255),
            40,
            sf::Color(0, 0, 0),
            3,
            false,
            true
        };

        // Draw coin quantity text
        TextRenderer::drawText(window, quantityLabel);
    }

    // Draw trade button
    tradeButton.draw(window);
}

// Get height of bar (varies depending on amount of required items)
int UITradeItemBar::getBarHeight()
{
    return requiredItems.size() * 100 + ((requiredCoins > 0) ? 100 : 0);
}