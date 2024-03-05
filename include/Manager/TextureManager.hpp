// TextureManager.hpp

#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

// Include libraries
#include <SFML/Graphics.hpp>
#include <PhysFsStream.hpp>
#include <unordered_map>
#include <string>

// Include headers
#include "Renderer/TextRenderer.hpp"
#include "Constants.hpp"

// Enum allowing textures to be referenced as types throughout the program
enum class TextureType
{
    PlayerShip,
    PlayerShipEngine,
    PlayerShipFlash,

    EnemyShip,
    EnemyShipEngine,
    EnemyShipFlash,
    EnemyShipDestroyed,

    Bullet,

    AsteroidCrack,
    AsteroidExplode,
    AsteroidFlash,

    SpaceStation,

    MercurySheet0, MercurySheet1, MercurySheet2,
    VenusSheet0, VenusSheet1, VenusSheet2,
    EarthSheet0, EarthSheet1, EarthSheet2,
    EarthBackground,
    MoonSheet0, MoonSheet1, MoonSheet2,
    MarsSheet0, MarsSheet1, MarsSheet2,
    JupiterSheet0, JupiterSheet1, JupiterSheet2,
    SaturnSheet0, SaturnSheet1, SaturnSheet2, SaturnSheet3,
    UranusSheet0, UranusSheet1, UranusSheet2,
    NeptuneSheet0, NeptuneSheet1, NeptuneSheet2,

    SilverCoin,
    PickupRock,
    PickupCopperChunk,
    PickupIronChunk,
    CopperBar,
    IronBar,
    CopronBar,
    TungstenChunk,
    TungstenBar,
    AluminiumChunk,
    AluminiumBar,

    PrototypeEngine,
    InterplanetaryEngine,
    InterplanetaryEngine2,
    InterplanetaryEngine3,
    UltimateInterplanetaryEngine,
    ShipCoolingSystem,
    SpeedIncrease,
    DamageIncrease,
    HealthIncrease,

    SymbolSpaceStation,
    SymbolEnemyMarker,

    SpaceStationMenuBackground,
    SpaceStationSubmenuBackground
};

// Struct containing data required to draw texture
struct TextureDrawData
{
    // Type of texture
    TextureType type;
    // Draw position on screen
    sf::Vector2f position;
    // Rotation
    sf::Angle rotation;
    // Scale
    float scale;
    // Whether texture should be drawn centred about its position
    bool centered = true;
    // The base colour the texture should be drawn in (white in most cases)
    sf::Color colour = sf::Color(255, 255, 255);
};

// Declaration of TextureManager class
class TextureManager
{

// Private TextureManager constructor, so class cannot be instantiated
// Creates static class behaviour
private:
    TextureManager() = delete;

// Public functions
public:
    // Load all textures into memory
    static bool loadTextures(sf::RenderWindow& window);

    // Draw texture using draw data
    static void drawTexture(sf::RenderWindow& window, TextureDrawData drawData);

    // Draw a section of a texture using draw data
    static void drawSubTexture(sf::RenderWindow& window, TextureDrawData drawData, sf::IntRect boundRect);

    // Get the size of a specific texture (width x height)
    inline static sf::Vector2u getTextureSize(TextureType type) {return textureMap.at(type).getSize();}

// Private functions
private:
    // Apply draw data before drawing a texture
    static void applyTextureData(TextureDrawData drawData);

// Private member variables
private:
    // Stores whether textures have been loaded
    static bool loadedTextures;

    // Stores loaded textures
    static std::unordered_map<TextureType, sf::Texture> textureMap;

    // Stores sprites, which provide an interface over the textures
    static std::unordered_map<TextureType, sf::Sprite> spriteMap;

    // Stores file path to each texture, so each texture can be loaded
    static const std::unordered_map<TextureType, std::string> texturePaths;

};

#endif