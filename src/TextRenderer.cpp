#include "TextRenderer.hpp"

sf::Font TextRenderer::font;
sf::Text TextRenderer::text;

bool TextRenderer::loadFont(std::string path) {

    bool successful = font.loadFromFile(path);
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

    window.draw(text);

}