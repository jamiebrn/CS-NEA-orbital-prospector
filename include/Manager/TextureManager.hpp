//
// TextureManager.hpp
// 
// Static class containing all loaded texture data, functions to load the texture data, and draw the textures to the screen.
//

#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

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

    SymbolSpaceStation,
    SymbolEnemyMarker,

    SpaceStationMenuBackground,
    SpaceStationSubmenuBackground
};

// Struct containing data required to draw texture
struct TextureDrawData
{
    TextureType type;
    sf::Vector2f position;
    sf::Angle rotation;
    float scale;
    bool centered = true;
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
    static bool loadTextures(sf::RenderWindow& window);

    static void drawTexture(sf::RenderWindow& window, TextureDrawData drawData);

    static void drawSubTexture(sf::RenderWindow& window, TextureDrawData drawData, sf::IntRect boundRect);

    inline static sf::Vector2u getTextureSize(TextureType type) {return textureMap.at(type).getSize();}

// Private functions
private:
    static void applyTextureData(TextureDrawData drawData);

// Private member variables
private:
    static bool loadedTextures;

    // Stores loaded textures
    static std::unordered_map<TextureType, sf::Texture> textureMap;

    static std::unordered_map<TextureType, sf::Sprite> spriteMap;

    // Stores relative path to each texture, so each texture can be loaded
    static const std::unordered_map<TextureType, std::string> texturePaths;

};

#endif