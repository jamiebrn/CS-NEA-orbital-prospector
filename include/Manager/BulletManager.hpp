#ifndef BULLET_MANAGER_HPP
#define BULLET_MANAGER_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "Objects/Bullet.hpp"

class BulletManager
{

private:
    BulletManager() = delete;

public:
    static void createBullet(sf::Vector2f position, sf::Angle rotation);

    static void updateBullets(float deltaTime);

    static void drawBullets(sf::RenderWindow& window);

    static void reset();

    static int getBulletCount();

private:
    static std::vector<Bullet> bullets;

};

#endif