#include "UI/UIButtonGroup.hpp"

void UIButtonGroup::addButton(std::string id, UIButtonData data)
{

    UIButton button;
    button.setPosition(data.position);
    button.setSize(data.size);
    button.setText(data.text);
    button.setColour(data.colour);
    button.setHoverColour(data.hoverColour);

    buttonMap[id] = button;

}

void UIButtonGroup::update(sf::Vector2f mousePos)
{

    for (auto& buttonIdPair : buttonMap)
    {
        UIButton& button = buttonIdPair.second;
        button.update(mousePos);
    }

}

bool UIButtonGroup::isButtonPressed(std::string id)
{

    if (buttonMap.count(id) == 0)
        return false;

    UIButton& button = buttonMap[id];

    return button.isHovering();

}

void UIButtonGroup::setButtonText(std::string id, std::string text)
{
    
    if (buttonMap.count(id) == 0)
        return;

    buttonMap[id].setText(text);

}

void UIButtonGroup::draw(sf::RenderWindow& window)
{

    for (auto& buttonIdPair : buttonMap)
    {
        UIButton& button = buttonIdPair.second;
        button.draw(window);
    }

}