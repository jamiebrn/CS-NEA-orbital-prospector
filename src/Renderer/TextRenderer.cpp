#include "Renderer/TextRenderer.hpp"

PhysFsStream TextRenderer::fontStream;
bool TextRenderer::loadedFont = false;
sf::Font TextRenderer::font;
sf::Text TextRenderer::text;

bool TextRenderer::loadFont(std::string path)
{

    loadedFont = false;

    if (!fontStream.open(path.c_str()))
    {
        return false;
    }   

    if (!font.loadFromStream(fontStream))
    {
        return false;
    }

    loadedFont = true;

    font.setSmooth(false);
    text.setFont(font);
    return true;
    
}

void TextRenderer::unloadFont()
{
    loadedFont = false;
    fontStream.close();
}

void TextRenderer::drawText(sf::RenderWindow& window, TextDrawData drawData)
{

    if (!loadedFont)
        return;

    text.setString(drawData.text);
    text.setPosition(drawData.position);
    text.setFillColor(drawData.colour);
    text.setCharacterSize(drawData.size);

    text.setOutlineColor(drawData.outlineColour);
    text.setOutlineThickness(drawData.outlineThickness);

    sf::Vector2f textCentre(0, 0);

    if (drawData.centeredX)
    {
        textCentre.x = text.getLocalBounds().getSize().x / 2.0f;
    }
    if (drawData.centeredY)
    {
        textCentre.y = text.getLocalBounds().getSize().y / 2.0f;
        textCentre.y += text.getLocalBounds().getPosition().y;
    }

    text.setOrigin(textCentre);

    window.draw(text);

}