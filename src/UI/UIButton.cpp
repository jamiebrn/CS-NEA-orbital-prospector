// UIButton.cpp

#include "UI/UIButton.hpp"

// Setter functions for member variables

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

// Update button using mouse position
void UIButton::update(sf::Vector2f mousePos)
{
    // Set button being hovered over to false by default
    hovering = false;

    // Calculate range of screen coordinates that the button is covering
    int minX = static_cast<int>(position.x);
    int minY = static_cast<int>(position.y);
    int maxX = static_cast<int>(position.x + size.x);
    int maxY = static_cast<int>(position.y + size.y);

    // If mouse cursor is within button bounds, set hovering to true
    if (mousePos.x >= minX && mousePos.y >= minY && mousePos.x <= maxX && mousePos.y <= maxY)
        hovering = true;

}

// Returns whether mouse cursor is hovering over button
bool UIButton::isHovering()
{
    return hovering;
}

// Draw button
void UIButton::draw(sf::RenderWindow& window)
{
    // Create rectangle representing button
    sf::RectangleShape rect(size);
    rect.setPosition(position);
    rect.setFillColor(colour);

    // If button is being hovered over by mouse cursor
    if (hovering)
    {
        // Create rectangle to draw as outline of button (as is being hovered over)
        sf::RectangleShape outlineRect(size + sf::Vector2f(6, 6));
        outlineRect.setPosition(position - sf::Vector2f(3, 3));
        outlineRect.setFillColor(sf::Color(255, 255, 255));

        // Draw button outline rectangle
        window.draw(outlineRect);

        // Set the button rectangle colour to the hover fill colour
        rect.setFillColor(hoverColour);
    }

    // Draw button rectangle
    window.draw(rect);

    // Create draw data for text object at centre of button
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

    // Draw text on button
    TextRenderer::drawText(window, drawData);
}