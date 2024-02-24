#ifndef PLANET_RENDERER_HPP
#define PLANET_RENDERER_HPP

#include <unordered_map>
#include <vector>

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
    Neptune,

    NONE
};

struct PlanetSheetData
{
    std::vector<TextureType> sheets;
    int xFrames, yFrames;
};

class PlanetRenderer
{

public:
    PlanetRenderer(PlanetType type);

    void update(float deltaTime);

    void draw(sf::RenderWindow& window, bool addCameraOffset = true);

    void setPlanetType(PlanetType newType);
    void setPosition(sf::Vector2f newPosition);
    void setScale(float newScale);

    sf::Vector2f getPosition();

private:
    static constexpr float ANIMATION_TICK_MAX = 0.09;

    PlanetType type;

    sf::Vector2f position;
    float scale;

    int animationXIndex, animationYIndex;
    int animationSheet;
    float animationTick;

    inline static const std::unordered_map<PlanetType, PlanetSheetData> planetTextureMap = {
        {PlanetType::Mercury, {{TextureType::MercurySheet0, TextureType::MercurySheet1, TextureType::MercurySheet2}, 20, 10}},
        {PlanetType::Venus, {{TextureType:: VenusSheet0, TextureType:: VenusSheet1, TextureType:: VenusSheet2}, 20, 10}},
        {PlanetType::Earth, {{TextureType::EarthSheet0, TextureType::EarthSheet1, TextureType::EarthSheet2}, 20, 10}},
        {PlanetType::Moon, {{TextureType::MoonSheet0, TextureType::MoonSheet1, TextureType::MoonSheet2}, 20, 10}},
        {PlanetType::Mars, {{TextureType::MarsSheet0, TextureType::MarsSheet1, TextureType::MarsSheet2}, 20, 10}},
        {PlanetType::Jupiter, {{TextureType::JupiterSheet0, TextureType::JupiterSheet1, TextureType::JupiterSheet2}, 20, 10}},
        {PlanetType::Saturn, {{TextureType::SaturnSheet0, TextureType::SaturnSheet1, TextureType::SaturnSheet2, TextureType::SaturnSheet3}, 15, 10}},
        {PlanetType::Uranus, {{TextureType::UranusSheet0, TextureType::UranusSheet1, TextureType::UranusSheet2}, 20, 10}},
        {PlanetType::Neptune, {{TextureType::NeptuneSheet0, TextureType::NeptuneSheet1, TextureType::NeptuneSheet2}, 20, 10}}
    };

};

#endif