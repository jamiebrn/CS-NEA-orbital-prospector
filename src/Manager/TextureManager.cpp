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

    {TextureType::MercurySheet0, "Data/Planets/Mercury0.png"},
    {TextureType::MercurySheet1, "Data/Planets/Mercury1.png"},
    {TextureType::MercurySheet2, "Data/Planets/Mercury2.png"},
    {TextureType::VenusSheet0, "Data/Planets/Venus0.png"},
    {TextureType::VenusSheet1, "Data/Planets/Venus1.png"},
    {TextureType::VenusSheet2, "Data/Planets/Venus2.png"},
    {TextureType::EarthSheet0, "Data/Planets/Earth0.png"},
    {TextureType::EarthSheet1, "Data/Planets/Earth1.png"},
    {TextureType::EarthSheet2, "Data/Planets/Earth2.png"},
    {TextureType::EarthBackground, "Data/Backgrounds/Earth Background.png"},
    {TextureType::MoonSheet0, "Data/Planets/Moon0.png"},
    {TextureType::MoonSheet1, "Data/Planets/Moon1.png"},
    {TextureType::MoonSheet2, "Data/Planets/Moon2.png"},
    {TextureType::MarsSheet0, "Data/Planets/Mars0.png"},
    {TextureType::MarsSheet1, "Data/Planets/Mars1.png"},
    {TextureType::MarsSheet2, "Data/Planets/Mars2.png"},
    {TextureType::JupiterSheet0, "Data/Planets/Jupiter0.png"},
    {TextureType::JupiterSheet1, "Data/Planets/Jupiter1.png"},
    {TextureType::JupiterSheet2, "Data/Planets/Jupiter2.png"},
    {TextureType::SaturnSheet0, "Data/Planets/Saturn0.png"},
    {TextureType::SaturnSheet1, "Data/Planets/Saturn1.png"},
    {TextureType::SaturnSheet2, "Data/Planets/Saturn2.png"},
    {TextureType::SaturnSheet3, "Data/Planets/Saturn3.png"},
    {TextureType::UranusSheet0, "Data/Planets/Uranus0.png"},
    {TextureType::UranusSheet1, "Data/Planets/Uranus1.png"},
    {TextureType::UranusSheet2, "Data/Planets/Uranus2.png"},
    {TextureType::NeptuneSheet0, "Data/Planets/Neptune0.png"},
    {TextureType::NeptuneSheet1, "Data/Planets/Neptune1.png"},
    {TextureType::NeptuneSheet2, "Data/Planets/Neptune2.png"},

    {TextureType::SilverCoin, "Data/UI/SilverCoin.png"},
    {TextureType::PickupRock, "Data/Pickups/Rock.png"},
    {TextureType::PickupCopperChunk, "Data/Pickups/CopperChunk.png"},
    {TextureType::PickupIronChunk, "Data/Pickups/IronChunk.png"},
    {TextureType::CopperBar, "Data/Pickups/CopperBar.png"},
    {TextureType::IronBar, "Data/Pickups/IronBar.png"},
    {TextureType::CopronBar, "Data/Pickups/CopronBar.png"},

    {TextureType::PrototypeEngine, "Data/Upgrades/PrototypeEngine.png"},

    {TextureType::SymbolSpaceStation, "Data/UI/SpaceStationSymbol.png"},
    {TextureType::SymbolEnemyMarker, "Data/UI/EnemyMarkerSymbol.png"},

    {TextureType::SpaceStationMenuBackground, "Data/UI/SpaceStationBackground.png"},
    {TextureType::SpaceStationSubmenuBackground, "Data/UI/SpaceStationSubmenuBackground.png"}
};

// Loads all textures from paths specified into texture map
bool TextureManager::loadTextures(sf::RenderWindow& window)
{
    if (loadedTextures)
        return true;
    
    loadedTextures = true;

    TextDrawData loadText = {
        "Loading textures",
        sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
        sf::Color(255, 255, 255),
        32,
        sf::Color(0, 0, 0),
        4,
        true,
        true
    };

    float texturesLoaded = 0;
    for (std::pair<TextureType, std::string> texturePair : texturePaths)
    {

        loadText.text = "Loading textures (" + std::to_string(static_cast<int>((texturesLoaded / texturePaths.size()) * 100)) + "%)";

        window.clear();

        std::string text = "Orbital Prospector";
        TextRenderer::drawText(window, {text, sf::Vector2f(WINDOW_WIDTH / 2, 150), sf::Color(255, 255, 255), 130, sf::Color(0, 0, 0), 4, true});

        TextRenderer::drawText(window, loadText);

        window.display();

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

        texturesLoaded++;
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