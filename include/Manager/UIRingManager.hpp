#ifndef UI_RING_MANAGER_HPP
#define UI_RING_MANAGER_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "Camera.hpp"
#include "Manager/TextureManager.hpp"
#include "Objects/EnemyShip.hpp"

class UIRingManager
{

private:
    UIRingManager() = delete;

public:
    static void update(sf::Vector2f stationPos, const std::vector<EnemyShip>& enemyShips);

    static void draw(sf::RenderWindow& window);

private:
    static sf::Vector2f calculateVector(sf::Vector2f targetPos);

private:
    static constexpr float RING_RADIUS = 300;

    static const sf::Vector2f MID_SCREEN;

    static sf::Vector2f stationVector;

    static std::vector<sf::Vector2f> enemyShipVectors;

};

#endif