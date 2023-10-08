#ifndef UI_BUTTON_HPP
#define UI_BUTTON_HPP

#include <SFML/Graphics.hpp>

#include "Renderer/TextRenderer.hpp"

struct UIButtonData
{
    sf::Vector2f position, size;
    std::string text;
    sf::Color colour, hoverColour;
    int fontSize = 32;
};

class UIButton
{

public:
    UIButton() = default;

    void setPosition(sf::Vector2f pos);
    void setSize(sf::Vector2f size);
    void setText(std::string text);
    void setColour(sf::Color colour);
    void setHoverColour(sf::Color colour);
    void setFontSize(int size);

    void update(sf::Vector2f mousePos);
    bool isHovering();

    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f position, size;
    std::string text;

    sf::Color colour;
    sf::Color hoverColour;

    int fontSize = 32;

    bool hovering;

};

#endif