// PlanetRenderer.hpp

#ifndef PLANET_RENDERER_HPP
#define PLANET_RENDERER_HPP

// Include libraries
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

// Include headers
#include "Manager/TextureManager.hpp"
#include "Camera.hpp"
#include "Constants.hpp"
#include "Helper.hpp"

// Enum containing all different types of planet
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

// Struct containing data relating to planet animation
struct PlanetSheetData
{
    std::vector<TextureType> sheets;
    int xFrames, yFrames;
};

// Declare planet renderer class
class PlanetRenderer
{

// Public class functions
public:
    // Constuctor taking in planet type as parameter
    PlanetRenderer(PlanetType type);

    // Update planet animation
    void update(float deltaTime);

    // Draw planet
    void draw(sf::RenderWindow& window, bool addCameraOffset = true);

    // Set planet type
    void setPlanetType(PlanetType newType);
    // Set planet position
    void setPosition(sf::Vector2f newPosition);
    // Set planet scale
    void setScale(float newScale);

    // Get planet position
    sf::Vector2f getPosition();

// Private member variables
private:
    // Constant storing amount of time per planet animation frame
    static constexpr float ANIMATION_TICK_MAX = 0.09;

    // Variable storing planet type
    PlanetType type;

    // Variables storing planet position and scale
    sf::Vector2f position;
    float scale;

    // Variables storing data related to planet animation playback
    int animationXIndex, animationYIndex;
    int animationSheet;
    float animationTick;

    // Constant map, storing each planet animaion playback data with the planet type as the key
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