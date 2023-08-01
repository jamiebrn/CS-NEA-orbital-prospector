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
    EarthBackground
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

    static void drawTexture(sf::RenderWindow& window, TextureType textureType, sf::Vector2f position, sf::Angle rotation, float scale);

    static void drawSubTexture(sf::RenderWindow& window, TextureType textureType, sf::Vector2f position, float scale, sf::IntRect boundRect);

// Private member variables
private:
    inline static bool loadedTextures = false;

    // Stores loaded textures
    inline static std::unordered_map<TextureType, sf::Texture> textureMap;

    // Stores relative path to each texture, so each texture can be loaded
    inline static const std::unordered_map<TextureType, std::string> texturePaths = {
        {TextureType::PlayerShip, "Space Ship Pack/Base/PNGs/Kla'ed - Fighter - Base.png"},
        {TextureType::EarthBackground, "Backgrounds/Earth Background.png"}
    };

};

#endif