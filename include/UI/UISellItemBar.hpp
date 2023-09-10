#ifndef UI_SELL_ITEM_BAR_HPP
#define UI_SELL_ITEM_BAR_HPP

#include <SFML/Graphics.hpp>

#include "UI/UIButton.hpp"
#include "Objects/ItemPickupType.hpp"
#include "Renderer/TextRenderer.hpp"
#include "Manager/InventoryManager.hpp"

class UISellItemBar
{

public:
    UISellItemBar(ItemPickupType type);

    void setPosition(sf::Vector2f position);
    void update(sf::Vector2f mousePos);
    bool sellButtonHovering();
    ItemPickupType getPickupType();

    void draw(sf::RenderWindow& window);

private:
    sf::Vector2f position;
    ItemPickupType itemType;
    UIButton sellButton;

};

#endif