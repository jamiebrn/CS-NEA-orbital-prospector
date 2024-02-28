// PlanetRenderer.cpp

#include "Renderer/PlanetRenderer.hpp"

// Constuctor taking in planet type as parameter
PlanetRenderer::PlanetRenderer(PlanetType type)
{
    // Set planet type from parameter
    this->type = PlanetType::Earth;

    // Initialise position and scale variables
    position = sf::Vector2f(0, 0);
    scale = 1;

    // Initialise planet animation variables
    animationXIndex = 0;
    animationYIndex = 0;
    animationSheet = 0;
    animationTick = 0;
}

// Update planet animation
void PlanetRenderer::update(float deltaTime)
{
    // Get animation spritesheet data for current planet type
    PlanetSheetData sheetData = planetTextureMap.at(type);

    // Increment animation by time
    animationTick += deltaTime;
    // If enough time passed, increment animation frame
    if (animationTick >= ANIMATION_TICK_MAX)
    {
        animationTick = 0;
        animationXIndex++;
        // Switch animation sprite sheet if end has been reached
        if (animationXIndex >= sheetData.xFrames)
        {
            animationXIndex = 0;
            animationSheet++;
            // If end of all sprite sheets has been reached, increment y index of frame
            if (animationSheet >= sheetData.sheets.size())
            {
                animationSheet = 0;
                animationYIndex = (animationYIndex + 1) % sheetData.yFrames;
            }
        }
    }
}

// Draw planet
void PlanetRenderer::draw(sf::RenderWindow& window, bool addCameraOffset)
{
    // Get animation spritesheet data for current planet type
    PlanetSheetData sheetData = planetTextureMap.at(type);

    // Get texture of current planet
    TextureType textureType = sheetData.sheets.at(animationSheet);

    // Create planet draw data
    TextureDrawData drawData = {
        textureType,
        position,
        sf::degrees(0),
        scale
    };

    // Add draw offset if required
    if (addCameraOffset)
        drawData.position += Camera::getDrawOffset() / PLANET_DEPTH_DIVIDE;
    
    // Calculate size of each animation frame on sprite sheet
    sf::Vector2u frameSize = TextureManager::getTextureSize(textureType);
    frameSize.x /= sheetData.xFrames;
    frameSize.y /= sheetData.yFrames;

    // Calculate frame of animation
    sf::IntRect subRect = sf::IntRect(sf::Vector2i(frameSize.x * animationXIndex, frameSize.y * animationYIndex), sf::Vector2i(frameSize.x, frameSize.y));

    // Draw planet sprite
    TextureManager::drawSubTexture(window, drawData, subRect);
}

// Set planet type
void PlanetRenderer::setPlanetType(PlanetType newType)
{
    // Set planet type
    type = newType;

    // Reset animation
    animationXIndex = 0;
    animationYIndex = 0;
    animationSheet = 0;
    animationTick = 0;
}

// Set planet position
void PlanetRenderer::setPosition(sf::Vector2f newPosition)
{
    position = newPosition;
}

// Set planet scale
void PlanetRenderer::setScale(float newScale)
{
    scale = newScale;
}

// Get planet position
sf::Vector2f PlanetRenderer::getPosition()
{
    return position;
}