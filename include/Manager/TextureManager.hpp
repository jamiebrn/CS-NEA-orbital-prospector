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

    Earth,
    EarthBackground,

    SilverCoin,
    PickupRock,
    PickupCopperChunk,
    PickupIronChunk,

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
    static bool loadTextures();

    static void drawTexture(sf::RenderWindow& window, TextureDrawData drawData);

    static void drawSubTexture(sf::RenderWindow& window, TextureDrawData drawData, sf::IntRect boundRect);

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