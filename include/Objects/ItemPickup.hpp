#ifndef ITEM_PICKUP_HPP
#define ITEM_PICKUP_HPP

#include <SFML/Graphics.hpp>

#include "Objects/DrawableObject.hpp"
#include "Objects/ItemPickupType.hpp"
#include "Manager/TextureManager.hpp"
#include "Camera.hpp"

class ItemPickup : public DrawableObject
{

public:
    ItemPickup(ItemPickupType type, sf::Vector2f position);

    void draw(sf::RenderWindow& window) override;

    sf::Vector2f getPosition();
    ItemPickupType getType();

private:
    sf::Vector2f position;

    ItemPickupType type;

};

#endif