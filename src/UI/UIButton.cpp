#include "UI/UIButton.hpp"

void UIButton::setPosition(sf::Vector2f pos)
{
    position = pos;
}

void UIButton::setSize(sf::Vector2f size)
{
    this->size = size;
}

void UIButton::setText(std::string text)
{
    this->text = text;
}

void UIButton::setColour(sf::Color colour)
{
    this->colour = colour;
}

void UIButton::setHoverColour(sf::Color colour)
{
    hoverColour = colour;
}

void UIButton::setFontSize(int size)
{
    fontSize = size;
}


void UIButton::update(sf::Vector2f mousePos)
{

    hovering = false;
    
    int minX = static_cast<int>(position.x);
    int minY = static_cast<int>(position.y);
    int maxX = static_cast<int>(position.x + size.x);
    int maxY = static_cast<int>(position.y + size.y);

    if (mousePos.x >= minX && mousePos.y >= minY && mousePos.x <= maxX && mousePos.y <= maxY)
        hovering = true;

}

bool UIButton::isHovering()
{
    return hovering;
}

void UIButton::draw(sf::RenderWindow& window)
{

    sf::RectangleShape rect(size);
    rect.setPosition(position);
    rect.setFillColor(colour);

    if (hovering)
    {
        sf::RectangleShape outlineRect(size + sf::Vector2f(6, 6));
        outlineRect.setPosition(position - sf::Vector2f(3, 3));
        outlineRect.setFillColor(sf::Color(255, 255, 255));

        window.draw(outlineRect);

        rect.setFillColor(hoverColour);
    }

    window.draw(rect);

    TextDrawData drawData = {
        text,
        position + sf::Vector2f(size.x / 2.0f, size.y / 2.0f),
        sf::Color(255, 255, 255),
        fontSize,
        sf::Color(0, 0, 0),
        3,
        true,
        true
    };

    TextRenderer::drawText(window, drawData);

}