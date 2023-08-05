#ifndef ENEMY_SHIP_HPP
#define ENEMY_SHIP_HPP

#include <SFML/Graphics.hpp>

#include "Camera.hpp"
#include "Manager/TextureManager.hpp"

class EnemyShip
{

public:
    EnemyShip(sf::Vector2f position);

    void update(sf::Vector2f playerPos, float deltaTime);

    void draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const;

private:
    sf::Vector2f position, velocity;
    sf::Angle rotation;

};

#endif