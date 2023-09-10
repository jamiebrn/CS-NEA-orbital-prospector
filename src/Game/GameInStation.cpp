#include "Game.hpp"

void Game::inStationLoop()
{

    // UI
    sf::Vector2i screenMousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = window.mapPixelToCoords(screenMousePosition);

    std::vector<UISellItemBar> sellItemBars;
    int yOffset = 0;
    for (auto itemTypePair : itemTextureMap)
    {

        ItemPickupType itemType = itemTypePair.first;

        UISellItemBar sellItemBar(itemType);
        sellItemBar.setPosition(sf::Vector2f(400, 300 + yOffset));
        sellItemBar.update(mousePosition);

        sellItemBars.push_back(sellItemBar);

        yOffset += 125;

    }

    sf::Event event;
    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::Closed)
            window.close();
        
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                changeState(GameState::InSpace);
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {

            if (event.mouseButton.button == sf::Mouse::Left)
            {
                for (UISellItemBar& sellItemBar : sellItemBars)
                {
                    if (sellItemBar.sellButtonHovering())
                    {
                        ItemPickupType itemType = sellItemBar.getPickupType();
                        int itemCount = InventoryManager::getItemCount(itemType);

                        InventoryManager::sellItems(itemType, itemCount);
                    }
                }
            }

        }

    }

    float deltaTime = clock.restart().asSeconds();

    window.clear(sf::Color(40, 40, 220));

    std::string text = "Space Station";
    TextRenderer::drawText(window, {text, sf::Vector2f(WINDOW_WIDTH / 2, 80), sf::Color(255, 255, 255), 100, sf::Color(0, 0, 0), 4, true});

    for (UISellItemBar& sellItemBar : sellItemBars)
    {
        sellItemBar.draw(window);
    }

    TextureDrawData drawData = {
        TextureType::SilverCoin,
        sf::Vector2f(200, 250),
        sf::degrees(0),
        5,
        false
    };

    TextureManager::drawTexture(window, drawData);

    text = std::to_string(InventoryManager::getSilverCoins());
    TextRenderer::drawText(window, {text, sf::Vector2f(270, 260), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3});

    text = "Exit (ESC)";
    TextRenderer::drawText(window, {text, sf::Vector2f(20, 980), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3});

    window.display();

}