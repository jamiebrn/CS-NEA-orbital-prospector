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

    EnemyShip,
    EnemyShipEngine,
    EnemyShipFlash,

    Bullet,

    AsteroidCrack,
    AsteroidExplode,
    AsteroidFlash,

    SpaceStation,

    Earth,
    EarthBackground,

    PickupRock,

    SymbolSpaceStation,
    SymbolEnemyMarker
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
    inline static bool loadedTextures = false;

    // Stores loaded textures
    inline static std::unordered_map<TextureType, sf::Texture> textureMap;

    inline static std::unordered_map<TextureType, sf::Sprite> spriteMap;

    // Stores relative path to each texture, so each texture can be loaded
    inline static const std::unordered_map<TextureType, std::string> texturePaths = {
        {TextureType::PlayerShip, "Space Ship Pack/Base/PNGs/Kla'ed - Fighter - Base.png"},
        {TextureType::PlayerShipEngine, "Space Ship Pack/Engine/PNGs/Kla'ed - Fighter - Engine.png"},
        
        {TextureType::EnemyShip, "Space Ship Pack/Base/PNGs/Kla'ed - Scout - Base.png"},
        {TextureType::EnemyShipEngine, "Space Ship Pack/Engine/PNGs/Kla'ed - Scout - Engine.png"},
        {TextureType::EnemyShipFlash, "Space Ship Pack/Base/PNGs/Kla'ed - Scout - Flash.png"},

        {TextureType::Bullet, "Space Ship Pack/Projectiles/PNGs/Kla'ed - Bullet.png"},
        
        {TextureType::AsteroidCrack, "Environment/Asteroids/PNGs/Asteroid 01 - Crack.png"},
        {TextureType::AsteroidExplode, "Environment/Asteroids/PNGs/Asteroid 01 - Explode.png"},
        {TextureType::AsteroidFlash, "Environment/Asteroids/PNGs/Asteroid 01 - Flash.png"},

        {TextureType::SpaceStation, "Space Ship Pack/Base/PNGs/Space Station.png"},

        {TextureType::Earth, "Planets/Earth.png"},
        {TextureType::EarthBackground, "Backgrounds/Earth Background.png"},

        {TextureType::PickupRock, "Pickups/Rock.png"},

        {TextureType::SymbolSpaceStation, "UI/SpaceStationSymbol.png"},
        {TextureType::SymbolEnemyMarker, "UI/EnemyMarkerSymbol.png"}
    };

};

#endif