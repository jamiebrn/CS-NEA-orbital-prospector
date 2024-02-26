// UIRingManager.hpp

#ifndef UI_RING_MANAGER_HPP
#define UI_RING_MANAGER_HPP

// Include libraries
#include <SFML/Graphics.hpp>
#include <vector>

// Include headers
#include "Constants.hpp"
#include "Camera.hpp"
#include "Manager/TextureManager.hpp"
#include "Objects/EnemyShip.hpp"

// Declare UI ring manager class
class UIRingManager
{

// Delete constructor as is static class
private:
    UIRingManager() = delete;

// Public class functions
public:
    // Update UI ring
    static void update(sf::Vector2f stationPos, const std::vector<EnemyShip>& enemyShips);

    // Draw UI ring
    static void draw(sf::RenderWindow& window);

// Private class functions
private:
    // Calculate vector of icon on UI ring
    static sf::Vector2f calculateVector(sf::Vector2f targetPos);

// Private member variables
private:
    // Constant storing radius of UI ring drawn on screen
    static constexpr float RING_RADIUS = 300;

    // Constant storing position of centre of screen
    static const sf::Vector2f MID_SCREEN;

    // Variable storing position of space station icon on UI ring
    static sf::Vector2f stationVector;

    // Vector storing positions of enemy ship icons on UI ring
    static std::vector<sf::Vector2f> enemyShipVectors;

};

#endif