#include "UI/UISellItemBar.hpp"

UISellItemBar::UISellItemBar(ItemPickupType type)
{

    itemType = type;

    sellButton.setText("Sell");
    sellButton.setSize(sf::Vector2f(150, 75));
    
}

void UISellItemBar::setPosition(sf::Vector2f position)
{
    this->position = position;
    sellButton.setPosition(position + sf::Vector2f(400, 12));
}

void UISellItemBar::update(sf::Vector2i mousePos)
{
    sellButton.update(mousePos);
}

bool UISellItemBar::sellButtonHovering()
{
    return sellButton.isHovering();
}

ItemPickupType UISellItemBar::getPickupType()
{
    return itemType;
}

void UISellItemBar::draw(sf::RenderWindow& window)
{

    sf::RectangleShape background(sf::Vector2f(600, 150));
    background.setPosition(position);
    background.setFillColor(sf::Color(20, 20, 20, 100));
    window.draw(background);

    TextureDrawData drawData = {
        itemTextureMap.at(itemType),
        position + sf::Vector2f(100, 123),
        sf::degrees(0),
        4
    };

    TextureManager::drawTexture(window, drawData);

    TextDrawData quantityLabel = {
        "x" + std::to_string(InventoryManager::getItemCount(itemType)),
        position + sf::Vector2f(180, 123),
        sf::Color(255, 255, 255),
        32,
        sf::Color(0, 0, 0),
        3,
        false,
        true
    };

    TextRenderer::drawText(window, quantityLabel);

    sellButton.draw(window);

}