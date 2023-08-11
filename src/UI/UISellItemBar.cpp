#include "UI/UISellItemBar.hpp"

UISellItemBar::UISellItemBar(ItemPickupType type)
{
    itemType = type;

    sellButton.setPosition(sf::Vector2f(50, 750));
    
}

void UISellItemBar::setPosition(sf::Vector2f position)
{
    this->position = position;
}

void UISellItemBar::draw(sf::RenderWindow& window)
{

}