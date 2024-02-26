// ItemPickupManager.hpp

#ifndef ITEM_PICKUP_MANAGER_HPP
#define ITEM_PICKUP_MANAGER_HPP

// Include libraries
#include <vector>
#include <SFML/Graphics.hpp>

// Include headers
#include "Objects/ItemPickupType.hpp"
#include "Objects/ItemPickup.hpp"

// Declare class
class ItemPickupManager
{

// Delete constructor, as is static class
private:
    ItemPickupManager() = delete;

// Public class functions
public:
    // Add item of type at specific position
    static void addItem(ItemPickupType type, sf::Vector2f position);

    // Test whether any items are being picked up, from a certain position with pickup radius
    static std::vector<ItemPickupType> testCollectedPickups(sf::Vector2f position, float radius);

    // Get reference to vector of items
    static std::vector<ItemPickup>& getPickups();

    // Draw all item pickups
    static void drawPickups(sf::RenderWindow& window);

    // Delete all item pickups
    static void reset();

// Private member variables
private:
    // Vector storing all item pickups
    static std::vector<ItemPickup> itemPickups;

};

#endif