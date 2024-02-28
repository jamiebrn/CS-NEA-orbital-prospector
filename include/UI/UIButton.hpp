// UIButton.hpp

#ifndef UI_BUTTON_HPP
#define UI_BUTTON_HPP

// Include libraries
#include <SFML/Graphics.hpp>

// Include headers
#include "Renderer/TextRenderer.hpp"

// Struct containing data, representing a button
struct UIButtonData
{
    sf::Vector2f position, size;
    std::string text;
    sf::Color colour, hoverColour;
    unsigned int fontSize = 32;
};

// Declare UI button class
class UIButton
{

// Public class functions
public:
    // Default constructor
    UIButton() = default;

    // Setter functions for member variables
    void setPosition(sf::Vector2f pos);
    void setSize(sf::Vector2f size);
    void setText(std::string text);
    void setColour(sf::Color colour);
    void setHoverColour(sf::Color colour);
    void setFontSize(int size);

    // Update button using mouse position
    void update(sf::Vector2f mousePos);

    // Returns whether mouse cursor is hovering over button
    bool isHovering();

    // Draw button
    void draw(sf::RenderWindow& window);

// Private member variables
private:
    // Position and size of button
    sf::Vector2f position, size;

    // Text drawn on button
    std::string text;

    // Colour and colour while hovering
    sf::Color colour;
    sf::Color hoverColour;

    // Font size of text drawn on button
    unsigned int fontSize = 32;

    // Whether button is being hovered over by mouse cursor
    bool hovering;
    
};

#endif