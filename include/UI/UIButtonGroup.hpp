// UIButtonGroup.hpp

#ifndef UI_BUTTON_GROUP
#define UI_BUTTON_GROUP

// Include libraries
#include <SFML/Graphics.hpp>
#include <unordered_map>

// Include headers
#include "UI/UIButton.hpp"

// Declare UI button group
// Container for multiple UI button objects
class UIButtonGroup
{

// Public class functions
public:
    // Default constructor
    UIButtonGroup() = default;

    // Add button to button group
    void addButton(std::string id, UIButtonData data);

    // Delete all buttons from group
    inline void clear() {buttonMap.clear();}

    // Get reference to the button group map
    inline const std::unordered_map<std::string, UIButton>& getButtonMap() {return buttonMap;}

    // Update all buttons using mouse position
    void update(sf::Vector2f mousePos);

    // Return whether a specific button is pressed (hovered over by mouse cursor)
    bool isButtonPressed(std::string id);

    // Set text of a specific button
    void setButtonText(std::string id, std::string text);

    // Draw all buttons to screen
    void draw(sf::RenderWindow& window);

// Private member variables
private:
    // Map storing all buttons
    std::unordered_map<std::string, UIButton> buttonMap;

// Public member variables
public:
    // Map used for general data storage
    // Useful as a button group is usually used for a whole UI state,
    // so having a place to store data about the UI state is cleaner
    // than having random variables scattered around the program.
    std::unordered_map<std::string, int> generalData;

};

#endif