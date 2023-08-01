#ifndef PLANET_RENDERER_HPP
#define PLANET_RENDERER_HPP

#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "TextureManager.hpp"
#include "Camera.hpp"

enum class PlanetType
{
    Earth
};

class PlanetRenderer
{

public:
    PlanetRenderer(PlanetType type);

    void update(float deltaTime);

    void draw(sf::RenderWindow& window);

    void setPlanetType(PlanetType newType);
    void setPosition(sf::Vector2f newPosition);
    void setScale(float newScale);

private:
    static const int ANIMATION_X_FRAMES = 60;
    static const int ANIMATION_Y_FRAMES = 10;
    static constexpr float ANIMATION_TICK_MAX = 0.06;

    PlanetType type;

    sf::Vector2f position;
    float scale;

    int animationXIndex, animationYIndex;
    float animationTick;

    inline static const std::unordered_map<PlanetType, TextureType> planetTextureMap = {
        {PlanetType::Earth, TextureType::Earth}
    };

};

#endif