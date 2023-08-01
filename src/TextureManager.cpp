#include "TextureManager.hpp"

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
    }

    if (!loadedTextures)
        return false;
    
    return true;
}

void TextureManager::drawTexture(sf::RenderWindow& window, TextureType textureType, sf::Vector2f position, sf::Angle rotation, float scale)
{

    if (!loadedTextures)
        return;

    sf::Sprite sprite;
    sprite.setTexture(textureMap[textureType]);

    sprite.setScale(sf::Vector2f(scale, scale));

    sf::FloatRect sizeRect = sprite.getLocalBounds();
    sf::Vector2f origin = sf::Vector2f(sizeRect.width / 2, sizeRect.height / 2);
    sprite.setOrigin(origin);

    sprite.setPosition(position);
    sprite.setRotation(rotation);

    window.draw(sprite);

}

void TextureManager::drawSubTexture(sf::RenderWindow& window, TextureType textureType, sf::Vector2f position, float scale, sf::IntRect boundRect)
{

    if (!loadedTextures)
        return;
    
    sf::Sprite sprite;
    sprite.setTexture(textureMap[textureType]);

    sprite.setScale(sf::Vector2f(scale, scale));
    sprite.setPosition(position);

    sprite.setTextureRect(boundRect);

    window.draw(sprite);

}