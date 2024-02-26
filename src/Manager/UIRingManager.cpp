// UIRingManager.cpp

#include "Manager/UIRingManager.hpp"

// Initialise member variables, as is static class
const sf::Vector2f UIRingManager::MID_SCREEN(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
sf::Vector2f UIRingManager::stationVector;
std::vector<sf::Vector2f> UIRingManager::enemyShipVectors;

// Update UI ring
void UIRingManager::update(sf::Vector2f stationPos, const std::vector<EnemyShip>& enemyShips)
{
    // Calculate vector of space station icon based on space station world position
    stationVector = calculateVector(stationPos);

    // Delete all enemy ship icon positions
    enemyShipVectors.clear();

    // For each enemy ship, add icon to UI ring
    for (const EnemyShip& ship : enemyShips)
    {
        // Calculate vector of enemy ship icon based on enemy ship world position
        sf::Vector2f shipVector = calculateVector(ship.getPosition());

        // Add position to vector
        enemyShipVectors.push_back(shipVector);
    }

}

// Calculate vector of icon on UI ring
sf::Vector2f UIRingManager::calculateVector(sf::Vector2f targetPos)
{
    // Get "camera position"
    sf::Vector2f camPos = -Camera::getDrawOffset();

    // Calculate relative vector from middle of screen in game world to target position
    sf::Vector2f vector = (targetPos - (camPos + MID_SCREEN));

    // Calculate radius of icon on UI ring
    float radius = std::min(RING_RADIUS, vector.length());

    // Calculate vector of icon on UI ring
    vector = vector.normalized() * radius;

    // Return calculated vector
    return vector;
}

// Draw UI ring
void UIRingManager::draw(sf::RenderWindow& window)
{
    // Create a circle with specific radius
    sf::CircleShape radius(RING_RADIUS);
    
    // Define circle as being a set of 500 points
    radius.setPointCount(500);

    // Set circle fill colour to be completely transparent, so is just outline
    radius.setFillColor(sf::Color(0, 0, 0, 0));

    // Set origin of circle to be at centre
    radius.setOrigin(sf::Vector2f(RING_RADIUS, RING_RADIUS));

    // Set outline colour of circle to be translucent white
    radius.setOutlineColor(sf::Color(230, 230, 230, 70));

    // Set outline of circle to be 2 pixels wide
    radius.setOutlineThickness(2);

    // Set circle position to be at centre of screen
    radius.setPosition(MID_SCREEN);

    // Draw circle to screen
    window.draw(radius);

    // If space station is not "inside" UI ring, draw the icon
    if (stationVector.lengthSq() >= (RING_RADIUS * RING_RADIUS) - 10)
    {
        // Create draw data for space station icon at calculated icon vector
        TextureDrawData drawData = {
            TextureType::SymbolSpaceStation,
            MID_SCREEN + stationVector,
            sf::degrees(0),
            2,
            true,
            sf::Color(255, 255, 255, 170)
        };

        // Draw space station UI ring icon
        TextureManager::drawTexture(window, drawData);
    }

    // Iterate over every enemy ship icon position, and attempt to draw the icon
    for (sf::Vector2f enemyShipVector : enemyShipVectors)
    {
        // If enemy ship vector is "inside" the UI ring, do not draw the icon and continue to next iteration
        if (enemyShipVector.lengthSq() < (RING_RADIUS * RING_RADIUS) - 10)
            continue;

        // Create draw data for enemy ship icon at calculate icon vector
        TextureDrawData drawData = {
            TextureType::SymbolEnemyMarker,
            MID_SCREEN + enemyShipVector,
            enemyShipVector.angle() + sf::degrees(90), // rotated to point towards enemy ship
            2,
            true,
            sf::Color(255, 255, 255, 170)
        };

        // Draw enemy ship UI ring icon
        TextureManager::drawTexture(window, drawData);
    }

}