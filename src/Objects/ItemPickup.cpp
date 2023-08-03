#include "Objects/ItemPickup.hpp"

ItemPickup::ItemPickup(ItemPickupType type, sf::Vector2f position)
{
    this->type = type;
    this->position = position;
}

void ItemPickup::draw(sf::RenderWindow& window)
{

    sf::Vector2f drawOffset = Camera::getDrawOffset();

    TextureType textureType = itemTextureMap.at(type);

    TextureDrawData drawData = {
        textureType,
        position + drawOffset,
        sf::degrees(0),
        4
    };

    TextureManager::drawTexture(window, drawData);

}

sf::Vector2f ItemPickup::getPosition()
{
    return position;
}

ItemPickupType ItemPickup::getType()
{
    return type;
}