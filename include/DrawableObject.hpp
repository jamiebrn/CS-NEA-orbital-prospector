//
// DrawableObject.hpp
// 
// Abstract base class that any object with a draw function will derive from
//

#ifndef DRAWABLE_OBJECT_HPP
#define DRAWABLE_OBJECT_HPP

#include <SFML/Graphics.hpp>

// Declaration of DrawableObject abstract class
class DrawableObject
{

public:
    // Pure virtual function "draw" which derived classes will inherit
    virtual void draw(sf::RenderWindow& window) = 0;

};

#endif