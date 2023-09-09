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
        sf::Vector2f itemPosition = iter->getPosition();
        float distanceSq = (position - itemPosition).lengthSq();

        if (distanceSq <= radius * radius)
        {
            collected.push_back(iter->getType());

            iter = itemPickups.erase(iter);

            continue;
        }

        iter++;
    }

    return collected;

}

std::vector<ItemPickup>& ItemPickupManager::getPickups()
{
    return itemPickups;
}

void ItemPickupManager::drawPickups(sf::RenderWindow& window)
{

    for (ItemPickup& itemPickup : itemPickups)
    {
        itemPickup.draw(window);
    }

}

void ItemPickupManager::empty()
{
    itemPickups.clear();
}