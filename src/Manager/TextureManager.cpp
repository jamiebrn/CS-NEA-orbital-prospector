#include "Manager/TextureManager.hpp"

bool TextureManager::loadedTextures = false;

// Stores loaded textures
std::unordered_map<TextureType, sf::Texture> TextureManager::textureMap;

std::unordered_map<TextureType, sf::Sprite> TextureManager::spriteMap;

const std::unordered_map<TextureType, std::string> TextureManager::texturePaths = {
    {TextureType::PlayerShip, "Data/Space Ship Pack/Base/PNGs/Kla'ed - Fighter - Base.png"},
    {TextureType::PlayerShipEngine, "Data/Space Ship Pack/Engine/PNGs/Kla'ed - Fighter - Engine.png"},
    {TextureType::PlayerShipFlash, "Data/Space Ship Pack/Base/PNGs/Kla'ed - Fighter - Flash.png"},
    
    {TextureType::EnemyShip, "Data/Space Ship Pack/Base/PNGs/Kla'ed - Scout - Base.png"},
    {TextureType::EnemyShipEngine, "Data/Space Ship Pack/Engine/PNGs/Kla'ed - Scout - Engine.png"},
    {TextureType::EnemyShipFlash, "Data/Space Ship Pack/Base/PNGs/Kla'ed - Scout - Flash.png"},
    {TextureType::EnemyShipDestroyed, "Data/Space Ship Pack/Destruction/PNGs/Kla'ed - Scout - Destruction.png"},

    {TextureType::Bullet, "Data/Space Ship Pack/Projectiles/PNGs/Kla'ed - Bullet.png"},
    
    {TextureType::AsteroidCrack, "Data/Environment/Asteroids/PNGs/Asteroid 01 - Crack.png"},
    {TextureType::AsteroidExplode, "Data/Environment/Asteroids/PNGs/Asteroid 01 - Explode.png"},
    {TextureType::AsteroidFlash, "Data/Environment/Asteroids/PNGs/Asteroid 01 - Flash.png"},

    {TextureType::SpaceStation, "Data/Space Ship Pack/Base/PNGs/Space Station.png"},

    {TextureType::Mercury, "Data/Planets/Mercury.png"},
    {TextureType::Venus, "Data/Planets/Venus.png"},
    {TextureType::Earth, "Data/Planets/Earth.png"},
    {TextureType::EarthBackground, "Data/Backgrounds/Earth Background.png"},
    {TextureType::Moon, "Data/Planets/Moon.png"},
    {TextureType::Mars, "Data/Planets/Mars.png"},
    {TextureType::Jupiter, "Data/Planets/Jupiter.png"},
    {TextureType::Saturn, "Data/Planets/Saturn.png"},
    {TextureType::Uranus, "Data/Planets/Uranus.png"},
    {TextureType::Neptune, "Data/Planets/Neptune.png"},

    {TextureType::SilverCoin, "Data/UI/SilverCoin.png"},
    {TextureType::PickupRock, "Data/Pickups/Rock.png"},
    {TextureType::PickupCopperChunk, "Data/Pickups/CopperChunk.png"},
    {TextureType::PickupIronChunk, "Data/Pickups/IronChunk.png"},
    {TextureType::CopperBar, "Data/Pickups/CopperBar.png"},
    {TextureType::IronBar, "Data/Pickups/IronBar.png"},

    {TextureType::SymbolSpaceStation, "Data/UI/SpaceStationSymbol.png"},
    {TextureType::SymbolEnemyMarker, "Data/UI/EnemyMarkerSymbol.png"},

    {TextureType::SpaceStationMenuBackground, "Data/UI/SpaceStationBackground.png"},
    {TextureType::SpaceStationSubmenuBackground, "Data/UI/SpaceStationSubmenuBackground.png"}
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