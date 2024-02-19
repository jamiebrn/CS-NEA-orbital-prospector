#include "Renderer/PlanetRenderer.hpp"

PlanetRenderer::PlanetRenderer(PlanetType type)
{
    this->type = PlanetType::Earth;

    position = sf::Vector2f(0, 0);
    scale = 1;

    animationXIndex = 0;
    animationYIndex = 0;
    animationSheet = 0;
    animationTick = 0;
}


void PlanetRenderer::update(float deltaTime)
{
    PlanetSheetData sheetData = planetTextureMap.at(type);

    animationTick += deltaTime;
    if (animationTick >= ANIMATION_TICK_MAX)
    {
        animationTick = 0;
        animationXIndex++;
        if (animationXIndex >= sheetData.xFrames)
        {
            animationXIndex = 0;
            animationSheet++;
            if (animationSheet >= sheetData.sheets.size())
            {
                animationSheet = 0;
                animationYIndex = (animationYIndex + 1) % sheetData.yFrames;
            }
        }
    }
}

void PlanetRenderer::draw(sf::RenderWindow& window)
{

    PlanetSheetData sheetData = planetTextureMap.at(type);
    TextureType textureType = sheetData.sheets.at(animationSheet);

    TextureDrawData drawData = {
        textureType,
        position + Camera::getDrawOffset() / PLANET_DEPTH_DIVIDE,
        sf::degrees(0),
        scale
    };

    sf::Vector2u frameSize = TextureManager::getTextureSize(textureType);
    frameSize.x /= sheetData.xFrames;
    frameSize.y /= sheetData.yFrames;

    sf::IntRect subRect = sf::IntRect(sf::Vector2i(frameSize.x * animationXIndex, frameSize.y * animationYIndex), sf::Vector2i(frameSize.x, frameSize.y));

    TextureManager::drawSubTexture(window, drawData, subRect);

}

void PlanetRenderer::setPlanetType(PlanetType newType)
{
    type = newType;
    animationXIndex = 0;
    animationYIndex = 0;
    animationSheet = 0;
    animationTick = 0;
}

void PlanetRenderer::setPosition(sf::Vector2f newPosition)
{
    position = newPosition;
}

void PlanetRenderer::setScale(float newScale)
{
    scale = newScale;
}

sf::Vector2f PlanetRenderer::getPosition()
{
    return position;
}