#ifndef UI_TRADE_ITEM_BAR_HPP
#define UI_TRADE_ITEM_BAR_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <optional>

#include "UI/UIButton.hpp"
#include "Objects/ItemPickupType.hpp"
#include "Renderer/TextRenderer.hpp"
#include "Manager/InventoryManager.hpp"
#include "Manager/SoundManager.hpp"

class UITradeItemBar
{

public:
    UITradeItemBar();

    void addRequiredItems(ItemPickupType itemType, int amount);
    void setRequiredCoins(int amount);

    void setOfferItem(ItemPickupType itemType);
    void setOfferCoins(int amount);

    void setTradeActionText(std::string text);
    void setTradeActionSound(SoundType type);

    void setPosition(sf::Vector2f position);
    void update(sf::Vector2f mousePos);

    bool tradeButtonHovering();
    void acceptTrade();

    void draw(sf::RenderWindow& window);
    int getBarHeight();

private:
    sf::Vector2f position;
    
    std::map<ItemPickupType, int> requiredItems;
    int requiredCoins;

    ItemPickupType offerItem;
    int offerCoins;

    UIButton tradeButton;

    std::optional<SoundType> tradeSound;

};

#endif