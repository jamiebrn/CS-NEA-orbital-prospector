#include "UI/UITradeItemBar.hpp"

UITradeItemBar::UITradeItemBar()
{

    requiredItems.clear();
    requiredCoins = 0;

    offerItem = ItemPickupType::NONE;
    offerCoins = 0;

    tradeButton.setText("Trade");
    tradeButton.setSize(sf::Vector2f(150, 75));
    tradeButton.setColour(sf::Color(20, 190, 20));
    tradeButton.setHoverColour(sf::Color(30, 200, 30));
    
}

void UITradeItemBar::addRequiredItems(ItemPickupType itemType, int amount)
{
    requiredItems[itemType] = amount;
}

void UITradeItemBar::setRequiredCoins(int amount)
{
    requiredCoins = amount;
}

void UITradeItemBar::setOfferItem(ItemPickupType itemType)
{
    offerItem = itemType;
}

void UITradeItemBar::setOfferCoins(int amount)
{
    offerCoins = amount;
}

void UITradeItemBar::setTradeActionText(std::string text)
{
    tradeButton.setText(text);
}

void UITradeItemBar::setPosition(sf::Vector2f position)
{
    this->position = position;
    tradeButton.setPosition(position + sf::Vector2f(400, 12));
}

void UITradeItemBar::update(sf::Vector2f mousePos)
{
    tradeButton.update(mousePos);
}

bool UITradeItemBar::tradeButtonHovering()
{
    return tradeButton.isHovering();
}

void UITradeItemBar::acceptTrade()
{
    for (std::pair<ItemPickupType, int> itemPair : requiredItems)
    {
        InventoryManager::addItem(itemPair.first, -itemPair.second);
    }

    InventoryManager::addSilverCoins(-requiredCoins);

    if (offerItem != ItemPickupType::NONE)
        InventoryManager::addItem(offerItem, 1);
    
    InventoryManager::addSilverCoins(offerCoins);
}

void UITradeItemBar::draw(sf::RenderWindow& window)
{

    sf::RectangleShape background(sf::Vector2f(600, getBarHeight()));
    background.setPosition(position);
    background.setFillColor(sf::Color(20, 20, 20, 100));
    window.draw(background);

    if (offerItem != ItemPickupType::NONE)
    {

        TextureDrawData drawData = {
            itemTextureMap.at(offerItem),
            position + sf::Vector2f(50, 50),
            sf::degrees(0),
            5
        };

        TextureManager::drawTexture(window, drawData);
        
    }

    if (offerCoins > 0)
    {

        TextureDrawData drawData = {
            TextureType::SilverCoin,
            position + sf::Vector2f(50, 50),
            sf::degrees(0),
            5
        };

        TextureManager::drawTexture(window, drawData);

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

        TextRenderer::drawText(window, quantityLabel);

    }

    int requiredItemYOffset = 50;

    for (std::pair<ItemPickupType, int> item : requiredItems)
    {

        TextureDrawData drawData = {
            itemTextureMap.at(item.first),
            position + sf::Vector2f(300, requiredItemYOffset),
            sf::degrees(0),
            5
        };

        TextureManager::drawTexture(window, drawData);

        TextDrawData quantityLabel = {
            std::to_string(item.second),
            position + sf::Vector2f(340, requiredItemYOffset),
            sf::Color(255, 255, 255),
            40,
            sf::Color(0, 0, 0),
            3,
            false,
            true
        };

        TextRenderer::drawText(window, quantityLabel);

        requiredItemYOffset += 100;

    }

    if (requiredCoins > 0)
    {

        TextureDrawData drawData = {
            TextureType::SilverCoin,
            position + sf::Vector2f(300, requiredItemYOffset),
            sf::degrees(0),
            5
        };

        TextureManager::drawTexture(window, drawData);

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

        TextRenderer::drawText(window, quantityLabel);

    }

    tradeButton.draw(window);

}

int UITradeItemBar::getBarHeight()
{
    return requiredItems.size() * 100 + ((requiredCoins > 0) ? 100 : 0);
}