// TextRenderer.hpp

#ifndef TEXT_RENDERER_HPP
#define TEXT_RENDERER_HPP

// Include libraries
#include <SFML/Graphics.hpp>
#include <PhysFsStream.hpp>
#include <string>

// Struct containing all data required when drawing text
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

// Declare text renderer class
class TextRenderer
{

// Delete constructor, as is static class
private:
    TextRenderer() = delete;

// Public class functions
public:
    // Load font into memory
    static bool loadFont(std::string path);

    // Unload font from memory
    static void unloadFont();

    // Draw text using draw data
    static void drawText(sf::RenderWindow& window, TextDrawData drawData);

// Private member variables
private:
    // Stream object, used to access font data
    static PhysFsStream fontStream;

    // Whether font has been loaded into memory
    static bool loadedFont;

    // Stores font
    static sf::Font font;

    // Text object used for drawing to screen
    static sf::Text text;

};

#endif