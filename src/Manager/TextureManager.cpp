#include "Manager/TextureManager.hpp"

bool TextureManager::loadedTextures = false;

// Stores loaded textures
std::unordered_map<TextureType, sf::Texture> TextureManager::textureMap;

std::unordered_map<TextureType, sf::Sprite> TextureManager::spriteMap;

const std::unordered_map<TextureType, std::string> TextureManager::texturePaths = {
    {TextureType::PlayerShip, "Space Ship Pack/Base/PNGs/Kla'ed - Fighter - Base.png"},
    {TextureType::PlayerShipEngine, "Space Ship Pack/Engine/PNGs/Kla'ed - Fighter - Engine.png"},
    {TextureType::PlayerShipFlash, "Space Ship Pack/Base/PNGs/Kla'ed - Fighter - Flash.png"},
    
    {TextureType::EnemyShip, "Space Ship Pack/Base/PNGs/Kla'ed - Scout - Base.png"},
    {TextureType::EnemyShipEngine, "Space Ship Pack/Engine/PNGs/Kla'ed - Scout - Engine.png"},
    {TextureType::EnemyShipFlash, "Space Ship Pack/Base/PNGs/Kla'ed - Scout - Flash.png"},
    {TextureType::EnemyShipDestroyed, "Space Ship Pack/Destruction/PNGs/Kla'ed - Scout - Destruction.png"},

    {TextureType::Bullet, "Space Ship Pack/Projectiles/PNGs/Kla'ed - Bullet.png"},
    
    {TextureType::AsteroidCrack, "Environment/Asteroids/PNGs/Asteroid 01 - Crack.png"},
    {TextureType::AsteroidExplode, "Environment/Asteroids/PNGs/Asteroid 01 - Explode.png"},
    {TextureType::AsteroidFlash, "Environment/Asteroids/PNGs/Asteroid 01 - Flash.png"},

    {TextureType::SpaceStation, "Space Ship Pack/Base/PNGs/Space Station.png"},

    {TextureType::Mercury, "Planets/Mercury.png"},
    {TextureType::Venus, "Planets/Venus.png"},
    {TextureType::Earth, "Planets/Earth.png"},
    {TextureType::EarthBackground, "Backgrounds/Earth Background.png"},
    {TextureType::Moon, "Planets/Moon.png"},
    {TextureType::Mars, "Planets/Mars.png"},
    {TextureType::Jupiter, "Planets/Jupiter.png"},
    {TextureType::Saturn, "Planets/Saturn.png"},
    {TextureType::Uranus, "Planets/Uranus.png"},
    {TextureType::Neptune, "Planets/Neptune.png"},

    {TextureType::SilverCoin, "UI/SilverCoin.png"},
    {TextureType::PickupRock, "Pickups/Rock.png"},
    {TextureType::PickupCopperChunk, "Pickups/CopperChunk.png"},
    {TextureType::PickupIronChunk, "Pickups/IronChunk.png"},
    {TextureType::CopperBar, "Pickups/CopperBar.png"},

    {TextureType::SymbolSpaceStation, "UI/SpaceStationSymbol.png"},
    {TextureType::SymbolEnemyMarker, "UI/EnemyMarkerSymbol.png"},

    {TextureType::SpaceStationMenuBackground, "UI/SpaceStationBackground.png"},
    {TextureType::SpaceStationSubmenuBackground, "UI/SpaceStationSubmenuBackground.png"}
};

// Loads all textures from paths specified into texture map
bool TextureManager::loadTextures()
{
    if (loadedTextures)
        return true;
    
    loadedTextures = true;

    for (std::pair<TextureType, std::string> texturePair : texturePaths)
    {
        TextureType textureType = texturePair.first;
        std::string texturePath = texturePair.second;

        sf::Texture texture;
        if (!texture.loadFromFile(texturePath))
        {
            loadedTextures = false;
            break;
        }

        texture.setRepeated(true);

        textureMap[textureType] = texture;

        sf::Sprite sprite;
        sprite.setTexture(textureMap[textureType]);

        spriteMap[textureType] = sprite;
    }

    if (!loadedTextures)
        return false;
    
    return true;
}

// Draw texture with specified data
void TextureManager::drawTexture(sf::RenderWindow& window, TextureDrawData drawData)
{

    if (!loadedTextures)
        return;
    
    sf::Sprite& sprite = spriteMap.at(drawData.type);

    applyTextureData(drawData);

    window.draw(sprite);

}

// Draw texture using a subrectangle, useful for spritesheets and tiling textures (subrectangle bigger than texture, texture repeats)
void TextureManager::drawSubTexture(sf::RenderWindow& window, TextureDrawData drawData, sf::IntRect boundRect)
{

    if (!loadedTextures)
        return;

    sf::Sprite& sprite = spriteMap.at(drawData.type);

    sprite.setTextureRect(boundRect);

    applyTextureData(drawData);

    window.draw(sprite);

}

void TextureManager::applyTextureData(TextureDrawData drawData)
{

    sf::Sprite& sprite = spriteMap.at(drawData.type);

    sprite.setScale(sf::Vector2f(drawData.scale, drawData.scale));

    sprite.setOrigin(sf::Vector2f(0, 0));
    if (drawData.centered)
    {
        sf::FloatRect sizeRect = sprite.getLocalBounds();
        sf::Vector2f origin = sf::Vector2f(sizeRect.width / 2.0f, sizeRect.height / 2.0f);
        sprite.setOrigin(origin);
    }

    sprite.setPosition(drawData.position);
    sprite.setRotation(drawData.rotation);

    sprite.setColor(drawData.colour);

}