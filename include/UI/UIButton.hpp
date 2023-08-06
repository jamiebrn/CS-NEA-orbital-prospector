#ifndef UI_BUTTON_HPP
#define UI_BUTTON_HPP

#include <SFML/Graphics.hpp>

#include "Renderer/TextRenderer.hpp"

class UIButton
{

public:
    UIButton() = default;

    void setPosition(sf::Vector2f pos);
    void setSize(sf::Vector2f size);
    void setText(std::string text);

    void update(sf::Vector2i mousePos);
    bool isHovering();

    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f position, size;
    std::string text;

    bool hovering;

};

#endif