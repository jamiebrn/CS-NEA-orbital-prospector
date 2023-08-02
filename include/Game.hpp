#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

#include "Constants.hpp"
#include "PlayerShip.hpp"
#include "TextureManager.hpp"
#include "Camera.hpp"
#include "PlanetRenderer.hpp"
#include "TextRenderer.hpp"

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
    PlayerShip playerShip;

};

#endif