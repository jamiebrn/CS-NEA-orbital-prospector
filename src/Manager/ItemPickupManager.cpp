#include "Manager/ItemPickupManager.hpp"

std::vector<ItemPickup> ItemPickupManager::itemPickups;

void ItemPickupManager::addItem(ItemPickupType type, sf::Vector2f position)
{
    ItemPickup itemPickup(type, position);

    itemPickups.push_back(itemPickup);
}

std::vector<ItemPickupType> ItemPickupManager::testCollectedPickups(sf::Vector2f position, float radius)
{

    std::vector<ItemPickupType> collected;

    for (auto iter = itemPickups.begin(); iter != itemPickups.end();)
    {
        float distance = (position - iter->getPosition()).lengthSq();

        if (distance <= radius * radius)
        {
            collected.push_back(iter->getType());

            iter = itemPickups.erase(iter);

            continue;
        }

        iter++;
    }

    return collected;

}

void ItemPickupManager::drawPickups(sf::RenderWindow& window)
{

    for (ItemPickup& itemPickup : itemPickups)
    {
        itemPickup.draw(window);
    }

}