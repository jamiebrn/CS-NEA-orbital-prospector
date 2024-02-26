#include "Game.hpp"

void Game::travellingLoop(float deltaTime)
{

    travelTime -= deltaTime;

    if (travelTime <= 0)
        targetGameState = GameState::InSpace;
    
    window.clear();

    TextRenderer::drawText(window, {
        "Travelling to \"" + static_cast<std::string>(magic_enum::enum_name(currentPlanet)) + 
        "\" (" + std::to_string(std::min(static_cast<int>(((TRAVEL_TIME - travelTime) / TRAVEL_TIME) * 100), 100)) + "%)",
        sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
        sf::Color(255, 255, 255),
        32,
        sf::Color(0, 0, 0),
        4,
        true,
        true
    });

}