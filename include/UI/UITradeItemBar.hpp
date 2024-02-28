// UITradeItemBar.hpp

#ifndef UI_TRADE_ITEM_BAR_HPP
#define UI_TRADE_ITEM_BAR_HPP

// Include libraries
#include <SFML/Graphics.hpp>
#include <map>
#include <optional>

// Include headers
#include "UI/UIButton.hpp"
#include "Objects/ItemPickupType.hpp"
#include "Renderer/TextRenderer.hpp"
#include "Manager/InventoryManager.hpp"
#include "Manager/UpgradeManager.hpp"
#include "Manager/SoundManager.hpp"

// Declare UI trade item bar class
// Multipurpose UI element that facilitates player trades
// Can accept coins and items as input, and can give coins, an item, or an upgrade as output
class UITradeItemBar
{

// Public class functions
public:
    // Constructor
    UITradeItemBar();

    // Add items that player needs to perform trade
    void addRequiredItems(ItemPickupType itemType, int amount);
    // Set amount of coins that player needs to perform trade
    void setRequiredCoins(int amount);

    // Set item that player is offered
    void setOfferItem(ItemPickupType itemType);
    // Set coins that player is offered
    void setOfferCoins(int amount);
    // Set upgrade that player is offered
    void setOfferUpgrade(UpgradeType upgrade);

    // Set text that is drawn on button which performs trade action
    void setTradeActionText(std::string text);
    // Set sound effect that plays when trade is performed
    void setTradeActionSound(SoundType type);

    // Set position of trade bar UI element
    void setPosition(sf::Vector2f position);
    // Update using mouse position, for trade button
    void update(sf::Vector2f mousePos);

    // Returns whether the trade button is being hovered over
    bool tradeButtonHovering();
    // Accept trade
    void acceptTrade();

    // Draw trade bar UI element
    void draw(sf::RenderWindow& window);

    // Get height of bar (varies depending on amount of required items)
    int getBarHeight();

// Private member variables
private:
    // Position on screen
    sf::Vector2f position;

    // Map storing all items required to perform trade
    std::map<ItemPickupType, int> requiredItems;
    // Variable storing coins required to perform trade
    int requiredCoins;

    // Item that is offered if trade is performed
    ItemPickupType offerItem;
    // Amount of coins offered if trade is performed
    int offerCoins;
    // Upgrade that is offered if trade is performed
    UpgradeType offerUpgrade;

    // Button object interacted with to perform trade
    UIButton tradeButton;

    // Sound played when trade is performed
    std::optional<SoundType> tradeSound;

};

#endif