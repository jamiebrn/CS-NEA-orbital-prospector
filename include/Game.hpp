#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Constants.hpp"
#include "Camera.hpp"
#include "Objects/PlayerShip.hpp"
#include "Objects/SpaceStation.hpp"
#include "Renderer/PlanetRenderer.hpp"
#include "Renderer/TextRenderer.hpp"
#include "Manager/TextureManager.hpp"
#include "Manager/BulletManager.hpp"
#include "Manager/AsteroidManager.hpp"
#include "Manager/ItemPickupManager.hpp"

class Game
{

public:
    Game();

    bool initialise();

    void mainLoop();

private:
    sf::RenderWindow window;
    sf::Image iconImage;

    sf::Clock clock;
    PlanetRenderer mainPlanetRenderer;
    SpaceStation spaceStation;
    PlayerShip playerShip;

};

#endif