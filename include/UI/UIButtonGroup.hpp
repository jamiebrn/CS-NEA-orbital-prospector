#ifndef UI_BUTTON_GROUP
#define UI_BUTTON_GROUP

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "UI/UIButton.hpp"

class UIButtonGroup
{

public:
    UIButtonGroup() = default;

    void addButton(std::string id, UIButtonData data);

    void update(sf::Vector2f mousePos);

    bool isButtonPressed(std::string id);

    void draw(sf::RenderWindow& window);

private:
    std::unordered_map<std::string, UIButton> buttonMap;

};

#endif