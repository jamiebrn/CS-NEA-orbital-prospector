#include "Manager/TextureManager.hpp"

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

    if (drawData.centered)
    {
        sf::FloatRect sizeRect = sprite.getLocalBounds();
        sf::Vector2f origin = sf::Vector2f(sizeRect.width / 2, sizeRect.height / 2);
        sprite.setOrigin(origin);
    }

    sprite.setPosition(drawData.position);
    sprite.setRotation(drawData.rotation);

}