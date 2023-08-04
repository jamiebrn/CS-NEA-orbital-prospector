#include "Manager/UIRingManager.hpp"

const sf::Vector2f UIRingManager::MID_SCREEN(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
sf::Vector2f UIRingManager::stationVector;

void UIRingManager::update(sf::Vector2f stationPos)
{

    sf::Vector2f camPos = -Camera::getDrawOffset();

    stationVector = (stationPos - (camPos + MID_SCREEN));
    float stationRadius = std::min(RING_RADIUS, stationVector.length());
    stationVector = stationVector.normalized() * stationRadius;

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

}