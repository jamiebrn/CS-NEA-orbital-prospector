// DrawableObject.hpp

#ifndef DRAWABLE_OBJECT_HPP
#define DRAWABLE_OBJECT_HPP

// Include libraries
#include <SFML/Graphics.hpp>

// Declaration of DrawableObject abstract class
class DrawableObject
{

public:
    // Pure virtual function "draw" which derived classes will inherit from
    virtual void draw(sf::RenderWindow& window) = 0;

};

#endif