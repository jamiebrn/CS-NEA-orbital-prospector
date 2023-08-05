#include "Manager/UIRingManager.hpp"

const sf::Vector2f UIRingManager::MID_SCREEN(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
sf::Vector2f UIRingManager::stationVector;
std::vector<sf::Vector2f> UIRingManager::enemyShipVectors;

void UIRingManager::update(sf::Vector2f stationPos, const std::vector<EnemyShip>& enemyShips)
{

    stationVector = calculateVector(stationPos);

    enemyShipVectors.clear();
    for (const EnemyShip& ship : enemyShips)
    {
        sf::Vector2f shipVector = calculateVector(ship.getPosition());

        enemyShipVectors.push_back(shipVector);
    }

}

sf::Vector2f UIRingManager::calculateVector(sf::Vector2f targetPos)
{
    sf::Vector2f camPos = -Camera::getDrawOffset();

    sf::Vector2f vector = (targetPos - (camPos + MID_SCREEN));
    float radius = std::min(RING_RADIUS, vector.length());
    vector = vector.normalized() * radius;

    return vector;
}

void UIRingManager::draw(sf::RenderWindow& window)
{

    sf::CircleShape radius(RING_RADIUS);
    radius.setPointCount(500);
    radius.setFillColor(sf::Color(0, 0, 0, 0));
    radius.setOrigin(sf::Vector2f(RING_RADIUS, RING_RADIUS));
    radius.setOutlineColor(sf::Color(230, 230, 230, 70));
    radius.setOutlineThickness(2);
    radius.setPosition(MID_SCREEN);

    window.draw(radius);

    if (stationVector.lengthSq() >= (RING_RADIUS * RING_RADIUS) - 10)
    {
        TextureDrawData drawData = {
            TextureType::SymbolSpaceStation,
            MID_SCREEN + stationVector,
            sf::degrees(0),
            2,
            true,
            sf::Color(255, 255, 255, 170)
        };

        TextureManager::drawTexture(window, drawData);
    }

    for (sf::Vector2f enemyShipVector : enemyShipVectors)
    {
        if (enemyShipVector.lengthSq() < (RING_RADIUS * RING_RADIUS) - 10)
            continue;

        TextureDrawData drawData = {
            TextureType::SymbolEnemyMarker,
            MID_SCREEN + enemyShipVector,
            enemyShipVector.angle() + sf::degrees(90),
            2,
            true,
            sf::Color(255, 255, 255, 170)
        };

        TextureManager::drawTexture(window, drawData);
    }

}