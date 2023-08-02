#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <SFML/Graphics.hpp>

#include "TextureManager.hpp"
#include "Camera.hpp"
#include "DrawableObject.hpp"

class Asteroid : public DrawableObject
{

public:
    Asteroid(sf::Vector2f position);

    void update(float deltaTime);

    void draw(sf::RenderWindow& window) override;

private:
    sf::Vector2f position;

};

#endif