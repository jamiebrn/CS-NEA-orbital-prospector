#include "PlanetRenderer.hpp"

PlanetRenderer::PlanetRenderer(PlanetType type)
{
    this->type = PlanetType::Earth;

    position = sf::Vector2f(0, 0);
    scale = 1;

    animationXIndex = 0;
    animationYIndex = 0;
    animationTick = 0;
}


void PlanetRenderer::update(float deltaTime)
{
    animationTick += deltaTime;
    if (animationTick >= ANIMATION_TICK_MAX)
    {
        animationTick = 0;
        animationXIndex++;
        if (animationXIndex >= ANIMATION_X_FRAMES)
        {
            animationXIndex = 0;
            animationYIndex = (animationYIndex + 1) % ANIMATION_Y_FRAMES;
        }
    }
}

void PlanetRenderer::draw(sf::RenderWindow& window)
{

    TextureType textureType = planetTextureMap.at(type);

    TextureDrawData drawData = {
        textureType,
        position + Camera::getDrawOffset() / 1.2f,
        sf::degrees(0),
        scale
    };

    sf::IntRect subRect = sf::IntRect(sf::Vector2i(200 * animationXIndex, 200 * animationYIndex), sf::Vector2i(200, 200));

    TextureManager::drawSubTexture(window, drawData, subRect);

}

void PlanetRenderer::setPlanetType(PlanetType newType)
{
    type = newType;
}

void PlanetRenderer::setPosition(sf::Vector2f newPosition)
{
    position = newPosition;
}

void PlanetRenderer::setScale(float newScale)
{
    scale = newScale;
}