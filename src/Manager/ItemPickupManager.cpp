// ItemPickupManager.cpp

#include "Manager/ItemPickupManager.hpp"

// Initialise member variables, as is static class
std::vector<ItemPickup> ItemPickupManager::itemPickups;

// Add item of type and position to manager
void ItemPickupManager::addItem(ItemPickupType type, sf::Vector2f position)
{
    // Create item pickup of specific type at specific position
    ItemPickup itemPickup(type, position);

    // Add item pickup to vector
    itemPickups.push_back(itemPickup);
}

// Test whether any items are being picked up, from a certain position with pickup radius
std::vector<ItemPickupType> ItemPickupManager::testCollectedPickups(sf::Vector2f position, float radius)
{

    // Create empty vector of items that have been collected
    std::vector<ItemPickupType> collected;

    // Iterate over all items in the item pickup vector, using an iterator
    for (auto iter = itemPickups.begin(); iter != itemPickups.end();)
    {
        // Get position of item pickup
        sf::Vector2f itemPosition = iter->getPosition();

        // Calculate square distance from test collect position to item position (faster than square root)
        float distanceSq = (position - itemPosition).lengthSq();

        // If square distance to item is within square radius, add item to collected vector and delete item from world
        if (distanceSq <= radius * radius)
        {
            // Add item to collected vector
            collected.push_back(iter->getType());

            // Delete item pickup from world
            iter = itemPickups.erase(iter);

            // Continue to next iteration
            continue;
        }

        // If not within collection radius, keep item and increment iterator
        iter++;
    }

    // Return vector of collected items
    return collected;

}

// Get reference to vector of items
std::vector<ItemPickup>& ItemPickupManager::getPickups()
{
    // Return reference
    return itemPickups;
}

// Draw all item pickups
void ItemPickupManager::drawPickups(sf::RenderWindow& window)
{
    // Iterate over all item pickups and draw them
    for (ItemPickup& itemPickup : itemPickups)
    {
        // Draw item pickup
        itemPickup.draw(window);
    }

}

// Delete all item pickups
void ItemPickupManager::reset()
{
    // Delete items
    itemPickups.clear();
}