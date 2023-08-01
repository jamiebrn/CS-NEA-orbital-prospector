#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

enum class TextureType
{
    PlayerShip,
    EarthBackground
};

class TextureManager
{

private:
    TextureManager() = delete;

public:
    static bool loadTextures();

    static void drawTexture(sf::RenderWindow& window, TextureType textureType, sf::Vector2f position, sf::Angle rotation, float scale);

    static void drawSubTexture(sf::RenderWindow& window, TextureType textureType, sf::Vector2f position, float scale, sf::IntRect boundRect);

private:
    inline static bool loadedTextures = false;

    inline static std::unordered_map<TextureType, sf::Texture> textureMap;

    inline static const std::unordered_map<TextureType, std::string> texturePaths = {
        {TextureType::PlayerShip, "Space Ship Pack/Base/PNGs/Kla'ed - Fighter - Base.png"},
        {TextureType::EarthBackground, "Backgrounds/Earth Background.png"}
    };

};

#endif