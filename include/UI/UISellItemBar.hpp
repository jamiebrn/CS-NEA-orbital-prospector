#ifndef UI_SELL_ITEM_BAR_HPP
#define UI_SELL_ITEM_BAR_HPP

#include <SFML/Graphics.hpp>

#include "UI/UIButton.hpp"
#include "Objects/ItemPickupType.hpp"

class UISellItemBar
{

public:
    UISellItemBar(ItemPickupType type);

    void setPosition(sf::Vector2f position);
    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f position;
    ItemPickupType itemType;
    UIButton sellButton;

};

#endif