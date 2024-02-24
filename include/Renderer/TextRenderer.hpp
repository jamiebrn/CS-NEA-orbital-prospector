#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

#include <string>

#include <SFML/Graphics.hpp>
#include <PhysFsStream.hpp>

struct TextDrawData
{
    std::string text;
    sf::Vector2f position;
    sf::Color colour;
    unsigned int size;

    sf::Color outlineColour = sf::Color(0, 0, 0);
    float outlineThickness = 0;

    bool centeredX = false;
    bool centeredY = false;
};

class TextRenderer {

private:
    TextRenderer() = delete;

public:
    static bool loadFont(std::string path);
    static void unloadFont();

    static void drawText(sf::RenderWindow& window, TextDrawData drawData);

private:
    static PhysFsStream fontStream;

    static bool loadedFont;
    static sf::Font font;
    static sf::Text text;

};

#endif