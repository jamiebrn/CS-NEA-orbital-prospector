#ifndef ITEM_PICKUP_MANAGER_HPP
#define ITEM_PICKUP_MANAGER_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "Objects/ItemPickupType.hpp"
#include "Objects/ItemPickup.hpp"

class ItemPickupManager
{

private:
    ItemPickupManager() = delete;

public:
    static void addItem(ItemPickupType type, sf::Vector2f position);

    static std::vector<ItemPickupType> testCollectedPickups(sf::Vector2f position, float radius);

    static void drawPickups(sf::RenderWindow& window);

private:
    static std::vector<ItemPickup> itemPickups;

};

#endif