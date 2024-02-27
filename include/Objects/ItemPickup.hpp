// ItemPickup.hpp

#ifndef ITEM_PICKUP_HPP
#define ITEM_PICKUP_HPP

// Include libraries
#include <SFML/Graphics.hpp>
#include <json.hpp>

// Include headers
#include "Objects/DrawableObject.hpp"
#include "Objects/ItemPickupType.hpp"
#include "Manager/TextureManager.hpp"
#include "Camera.hpp"

// Structure containing all item pickup data
struct ItemPickupData
{
    // Position
    float x, y;
    // Type of item
    ItemPickupType type;

    // Macro used for (de)serialising the struct
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ItemPickupData, x, y, type)
};

// Declare item pickup class
class ItemPickup : public DrawableObject
{

// Public class functions
public:
    // Constructor taking in type of item and position as parameters
    ItemPickup(ItemPickupType type, sf::Vector2f position);

    // Draw item pickup
    void draw(sf::RenderWindow& window) override;

    // Get position of item pickup
    sf::Vector2f getPosition();

    // Get type of item pickup
    ItemPickupType getType();

// Private member variables
private:
    // Variable storing position of item pickup
    sf::Vector2f position;

    // Variable storing type of item pickup
    ItemPickupType type;

};



#endif