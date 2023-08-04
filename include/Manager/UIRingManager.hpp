#ifndef UI_RING_MANAGER_HPP
#define UI_RING_MANAGER_HPP

#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "Camera.hpp"
#include "Manager/TextureManager.hpp"

class UIRingManager
{

private:
    UIRingManager() = delete;

public:
    static void update(sf::Vector2f stationPos);

    static void draw(sf::RenderWindow& window);

private:
    static constexpr float RING_RADIUS = 300;

    static const sf::Vector2f MID_SCREEN;

    static sf::Vector2f stationVector;

};

#endif