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

    {TextureType::MercurySheet0, "Planets/Mercury0.png"},
    {TextureType::MercurySheet1, "Planets/Mercury1.png"},
    {TextureType::MercurySheet2, "Planets/Mercury2.png"},
    {TextureType::VenusSheet0, "Planets/Venus0.png"},
    {TextureType::VenusSheet1, "Planets/Venus1.png"},
    {TextureType::VenusSheet2, "Planets/Venus2.png"},
    {TextureType::EarthSheet0, "Planets/Earth0.png"},
    {TextureType::EarthSheet1, "Planets/Earth1.png"},
    {TextureType::EarthSheet2, "Planets/Earth2.png"},
    {TextureType::EarthBackground, "Backgrounds/Earth Background.png"},
    {TextureType::MoonSheet0, "Planets/Moon0.png"},
    {TextureType::MoonSheet1, "Planets/Moon1.png"},
    {TextureType::MoonSheet2, "Planets/Moon2.png"},
    {TextureType::MarsSheet0, "Planets/Mars0.png"},
    {TextureType::MarsSheet1, "Planets/Mars1.png"},
    {TextureType::MarsSheet2, "Planets/Mars2.png"},
    {TextureType::JupiterSheet0, "Planets/Jupiter0.png"},
    {TextureType::JupiterSheet1, "Planets/Jupiter1.png"},
    {TextureType::JupiterSheet2, "Planets/Jupiter2.png"},
    {TextureType::SaturnSheet0, "Planets/Saturn0.png"},
    {TextureType::SaturnSheet1, "Planets/Saturn1.png"},
    {TextureType::SaturnSheet2, "Planets/Saturn2.png"},
    {TextureType::SaturnSheet3, "Planets/Saturn3.png"},
    {TextureType::UranusSheet0, "Planets/Uranus0.png"},
    {TextureType::UranusSheet1, "Planets/Uranus1.png"},
    {TextureType::UranusSheet2, "Planets/Uranus2.png"},
    {TextureType::NeptuneSheet0, "Planets/Neptune0.png"},
    {TextureType::NeptuneSheet1, "Planets/Neptune1.png"},
    {TextureType::NeptuneSheet2, "Planets/Neptune2.png"},

    {TextureType::SilverCoin, "UI/SilverCoin.png"},
    {TextureType::PickupRock, "Pickups/Rock.png"},
    {TextureType::PickupCopperChunk, "Pickups/CopperChunk.png"},
    {TextureType::PickupIronChunk, "Pickups/IronChunk.png"},
    {TextureType::CopperBar, "Pickups/CopperBar.png"},
    {TextureType::IronBar, "Pickups/IronBar.png"},
    {TextureType::CopronBar, "Pickups/CopronBar.png"},
    {TextureType::TungstenChunk, "Pickups/TungstenChunk.png"},
    {TextureType::TungstenBar, "Pickups/TungstenBar.png"},
    {TextureType::AluminiumChunk, "Pickups/AluminiumChunk.png"},
    {TextureType::AluminiumBar, "Pickups/AluminiumBar.png"},

    {TextureType::PrototypeEngine, "Upgrades/PrototypeEngine.png"},
    {TextureType::InterplanetaryEngine, "Upgrades/InterplanetaryEngine.png"},
    {TextureType::InterplanetaryEngine2, "Upgrades/InterplanetaryEngine2.png"},
    {TextureType::InterplanetaryEngine3, "Upgrades/InterplanetaryEngine3.png"},
    {TextureType::UltimateInterplanetaryEngine, "Upgrades/UltimateInterplanetaryEngine.png"},
    {TextureType::ShipCoolingSystem, "Upgrades/CoolingSystem.png"},

    {TextureType::SymbolSpaceStation, "UI/SpaceStationSymbol.png"},
    {TextureType::SymbolEnemyMarker, "UI/EnemyMarkerSymbol.png"},

    {TextureType::SpaceStationMenuBackground, "UI/SpaceStationBackground.png"},
    {TextureType::SpaceStationSubmenuBackground, "UI/SpaceStationSubmenuBackground.png"}
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

        PhysFsStream textureStream;
        if (!textureStream.open(texturePath.c_str()))
        {
            loadedTextures = false;
            break;
        }

        sf::Texture texture;
        if (!texture.loadFromStream(textureStream))
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