#ifndef PLANET_RENDERER_HPP
#define PLANET_RENDERER_HPP

#include <unordered_map>

#include <SFML/Graphics.hpp>

#include "Manager/TextureManager.hpp"
#include "Camera.hpp"
#include "Constants.hpp"
#include "Helper.hpp"

enum class PlanetType
{
    Mercury,
    Venus,

    Earth,
    Moon,

    Mars,
    Jupiter,
    Saturn,
    Uranus,
    Neptune
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

    sf::Vector2f getPosition();

private:
    static constexpr int ANIMATION_X_FRAMES = 60;
    static constexpr int ANIMATION_Y_FRAMES = 10;
    static constexpr float ANIMATION_TICK_MAX = 0.09;

    PlanetType type;

    sf::Vector2f position;
    float scale;

    int animationXIndex, animationYIndex;
    float animationTick;

    inline static const std::unordered_map<PlanetType, TextureType> planetTextureMap = {
        {PlanetType::Mercury, TextureType::Mercury},
        {PlanetType::Venus, TextureType:: Venus},
        {PlanetType::Earth, TextureType::Earth},
        {PlanetType::Moon, TextureType::Moon},
        {PlanetType::Mars, TextureType::Mars},
        {PlanetType::Jupiter, TextureType::Jupiter},
        {PlanetType::Saturn, TextureType::Saturn},
        {PlanetType::Uranus, TextureType::Uranus},
        {PlanetType::Neptune, TextureType::Neptune}
    };

};

#endif