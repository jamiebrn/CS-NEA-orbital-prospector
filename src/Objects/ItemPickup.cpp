// ItemPickup.cpp

#include "Objects/ItemPickup.hpp"

// Constructor taking in type of item and position as parameters
ItemPickup::ItemPickup(ItemPickupType type, sf::Vector2f position)
{
    // Set item pickup data from parameters
    this->type = type;
    this->position = position;
}

// Draw item pickup
void ItemPickup::draw(sf::RenderWindow& window)
{
    // If not in player view, do not draw
    if (!Camera::isInView(position, sf::Vector2f(100, 100)))
        return;
    
    // Get camera draw offset
    sf::Vector2f drawOffset = Camera::getDrawOffset();

    // Get texture corresponding to the item type
    TextureType textureType = itemTextureMap.at(type);

    // Create draw data for the item pickup
    TextureDrawData drawData = {
        textureType,
        position + drawOffset,
        sf::degrees(0),
        4
    };

    // Draw item pickup texture using draw data
    TextureManager::drawTexture(window, drawData);

}

// Get position of item pickup
sf::Vector2f ItemPickup::getPosition()
{
    return position;
}

// Get type of item pickup
ItemPickupType ItemPickup::getType()
{
    return type;
}