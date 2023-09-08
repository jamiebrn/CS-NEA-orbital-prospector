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