// UIButtonGroup.cpp

#include "UI/UIButtonGroup.hpp"

// Add button to button group
void UIButtonGroup::addButton(std::string id, UIButtonData data)
{
    // Create button
    UIButton button;

    // Set button data from data parameter
    button.setPosition(data.position);
    button.setSize(data.size);
    button.setText(data.text);
    button.setColour(data.colour);
    button.setHoverColour(data.hoverColour);
    button.setFontSize(data.fontSize);

    // Store button in hashmap
    buttonMap[id] = button;
}

// Update all buttons using mouse position
void UIButtonGroup::update(sf::Vector2f mousePos)
{
    // Iterate over all buttons and update
    for (auto& buttonIdPair : buttonMap)
    {
        // Get button from hashmap
        UIButton& button = buttonIdPair.second;
        // Update button using mouse position
        button.update(mousePos);
    }

}

// Return whether a specific button is pressed (hovered over by mouse cursor)
bool UIButtonGroup::isButtonPressed(std::string id)
{
    // If button ID does not exist in map, return false by default
    if (buttonMap.count(id) == 0)
        return false;
    
    // Get button from hashmap
    UIButton& button = buttonMap[id];

    // Return whether the button is being hovered over by the mouse cursor
    return button.isHovering();
}

// Set text of a specific button
void UIButtonGroup::setButtonText(std::string id, std::string text)
{
    // If button ID does not exist in map, do not attempt to set its text
    if (buttonMap.count(id) == 0)
        return;
    
    // Set text of button from hashmap
    buttonMap[id].setText(text);
}

// Draw all buttons to screen
void UIButtonGroup::draw(sf::RenderWindow& window)
{
    // Iterate over all buttons and draw
    for (auto& buttonIdPair : buttonMap)
    {
        // Get button from hashmap
        UIButton& button = buttonIdPair.second;
        // Draw button
        button.draw(window);
    }
}