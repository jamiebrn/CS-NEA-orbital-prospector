#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

#include <string>

#include <SFML/Graphics.hpp>

struct TextDrawData
{
    std::string text;
    sf::Vector2f position;
    sf::Color colour;
    unsigned int size;

    sf::Color outlineColour = sf::Color(0, 0, 0);
    float outlineThickness = 0;
};

class TextRenderer {

private:
    TextRenderer() = delete;

public:
    static bool loadFont(std::string path);

    static void drawText(sf::RenderWindow& window, TextDrawData drawData);

private:
    static sf::Font font;
    static sf::Text text;

};

#endif