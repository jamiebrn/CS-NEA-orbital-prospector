#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <algorithm>

#include <SFML/Graphics.hpp>

#include "Constants.hpp"
#include "Helper.hpp"

class Camera
{

private:
    Camera() = delete;

public:
    static void update(sf::Vector2f playerPosition, float deltaTime);

    static sf::Vector2f getDrawOffset();
    
    static void setOffset(sf::Vector2f newOffset);

private:
    static constexpr float MOVE_LERP_WEIGHT = 3.5;

    static sf::Vector2f offset;

};

#endif