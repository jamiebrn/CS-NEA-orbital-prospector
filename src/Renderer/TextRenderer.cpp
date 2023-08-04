#include "Renderer/TextRenderer.hpp"

sf::Font TextRenderer::font;
sf::Text TextRenderer::text;

bool TextRenderer::loadFont(std::string path) {

    bool successful = font.loadFromFile(path);
    font.setSmooth(false);
    text.setFont(font);
    return successful;
    
}

void TextRenderer::drawText(sf::RenderWindow& window, TextDrawData drawData) {
    
    text.setString(drawData.text);
    text.setPosition(drawData.position);
    text.setFillColor(drawData.colour);
    text.setCharacterSize(drawData.size);

    text.setOutlineColor(drawData.outlineColour);
    text.setOutlineThickness(drawData.outlineThickness);

    text.setOrigin(sf::Vector2f(0, 0));

    if (drawData.centered)
    {
        sf::Vector2f textCentre = text.getLocalBounds().getSize() / 2.0f;
        text.setOrigin(textCentre);
    }

    window.draw(text);

}