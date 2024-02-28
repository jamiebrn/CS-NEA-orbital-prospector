// TextRenderer.cpp

#include "Renderer/TextRenderer.hpp"

// Initialise member variables, as is static class
PhysFsStream TextRenderer::fontStream;
bool TextRenderer::loadedFont = false;
sf::Font TextRenderer::font;
sf::Text TextRenderer::text;

// Load font into memory
bool TextRenderer::loadFont(std::string path)
{
    // Set loaded font to false by default
    loadedFont = false;

    // If cannot load font into stream object, return false (unsuccessful load)
    if (!fontStream.open(path.c_str()))
    {
        return false;
    }

    // If cannot load font data from stream object into font object, return false (unsuccessful load)
    if (!font.loadFromStream(fontStream))
    {
        return false;
    }

    // Set loaded font to true, as font has been loaded
    loadedFont = true;

    // Disable font anti-alisaing
    font.setSmooth(false);
    // Load font object into text object
    text.setFont(font);

    // Return true by default (successful load)
    return true;
}

// Unload font from memory
void TextRenderer::unloadFont()
{
    // Sets font loaded to false
    loadedFont = false;
    // Close stream object containing font data
    fontStream.close();
}

// Draw text using draw data
void TextRenderer::drawText(sf::RenderWindow& window, TextDrawData drawData)
{
    // If font not loaded, do not draw text
    if (!loadedFont)
        return;
    
    // Set text data from draw data
    text.setString(drawData.text);
    text.setPosition(drawData.position);
    text.setFillColor(drawData.colour);
    text.setCharacterSize(drawData.size);
    text.setOutlineColor(drawData.outlineColour);
    text.setOutlineThickness(drawData.outlineThickness);

    // Set text centre to top left by default
    sf::Vector2f textCentre(0, 0);

    // If centre X value, set centre to middle X value
    if (drawData.centeredX)
    {
        textCentre.x = text.getLocalBounds().getSize().x / 2.0f;
    }
    // If centre Y value, set centre to middle Y value
    if (drawData.centeredY)
    {
        textCentre.y = text.getLocalBounds().getSize().y / 2.0f;
        textCentre.y += text.getLocalBounds().getPosition().y;
    }

    // Apply calculted centre as origin
    text.setOrigin(textCentre);

    // Draw text to window
    window.draw(text);
}