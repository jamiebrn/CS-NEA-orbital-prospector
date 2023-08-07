#include "Game.hpp"

void Game::inStationLoop()
{

    // UI
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    UIButton buttonSellRock;
    buttonSellRock.setPosition(sf::Vector2f(600, 400));
    buttonSellRock.setSize(sf::Vector2f(150, 60));
    buttonSellRock.setText("Sell");
    buttonSellRock.update(mousePos);

    UIButton buttonSellCopperChunk;
    buttonSellCopperChunk.setPosition(sf::Vector2f(600, 500));
    buttonSellCopperChunk.setSize(sf::Vector2f(150, 60));
    buttonSellCopperChunk.setText("Sell");
    buttonSellCopperChunk.update(mousePos);

    UIButton buttonSellIronChunk;
    buttonSellIronChunk.setPosition(sf::Vector2f(600, 600));
    buttonSellIronChunk.setSize(sf::Vector2f(150, 60));
    buttonSellIronChunk.setText("Sell");
    buttonSellIronChunk.update(mousePos);

    sf::Event event;
    while (window.pollEvent(event))
    {

        if (event.type == sf::Event::Closed)
            window.close();
        
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                gameState = GameState::InSpace;
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {

            if (event.mouseButton.button == sf::Mouse::Left)
            {
                if (buttonSellRock.isHovering())
                {
                    int count = InventoryManager::getItemCount(ItemPickupType::Rock);
                    InventoryManager::addItem(ItemPickupType::Rock, -count);
                    InventoryManager::addSilverCoins(count * 2);
                }
                else if (buttonSellCopperChunk.isHovering())
                {
                    int count = InventoryManager::getItemCount(ItemPickupType::CopperChunk);
                    InventoryManager::addItem(ItemPickupType::CopperChunk, -count);
                    InventoryManager::addSilverCoins(count * 4);
                }
                else if (buttonSellIronChunk.isHovering())
                {
                    int count = InventoryManager::getItemCount(ItemPickupType::IronChunk);
                    InventoryManager::addItem(ItemPickupType::IronChunk, -count);
                    InventoryManager::addSilverCoins(count * 5);
                }
            }

        }

    }

    float deltaTime = clock.restart().asSeconds();

    window.clear(sf::Color(40, 40, 220));

    std::string text = "Space Station";
    TextRenderer::drawText(window, {text, sf::Vector2f(WINDOW_WIDTH / 2, 80), sf::Color(255, 255, 255), 100, sf::Color(0, 0, 0), 4, true});

    TextureDrawData drawData = {
        TextureType::PickupRock,
        sf::Vector2f(300, 400),
        sf::degrees(0),
        5,
        false
    };

    TextureManager::drawTexture(window, drawData);

    drawData.type = TextureType::PickupCopperChunk;
    drawData.position = sf::Vector2f(300, 500);
    TextureManager::drawTexture(window, drawData);

    drawData.type = TextureType::PickupIronChunk;
    drawData.position = sf::Vector2f(300, 600);
    TextureManager::drawTexture(window, drawData);

    drawData.type = TextureType::SilverCoin;
    drawData.position = sf::Vector2f(200, 250);
    TextureManager::drawTexture(window, drawData);

    text = std::to_string(InventoryManager::getItemCount(ItemPickupType::Rock));
    TextRenderer::drawText(window, {text, sf::Vector2f(370, 410), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3});

    text = std::to_string(InventoryManager::getItemCount(ItemPickupType::CopperChunk));
    TextRenderer::drawText(window, {text, sf::Vector2f(370, 510), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3});

    text = std::to_string(InventoryManager::getItemCount(ItemPickupType::IronChunk));
    TextRenderer::drawText(window, {text, sf::Vector2f(370, 610), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3});

    text = std::to_string(InventoryManager::getSilverCoins());
    TextRenderer::drawText(window, {text, sf::Vector2f(270, 260), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3});

    buttonSellRock.draw(window);
    buttonSellCopperChunk.draw(window);
    buttonSellIronChunk.draw(window);

    text = "Exit (ESC)";
    TextRenderer::drawText(window, {text, sf::Vector2f(20, 980), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3});

    window.display();

}