#include "Game.hpp"

Game::Game()
    : playerShip(sf::Vector2f(0, 0)),
    mainPlanetRenderer(PlanetType::Earth)
{}

bool Game::initialise()
{

    srand((unsigned)time(0));

    window.create(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), WINDOW_TITLE, sf::Style::Titlebar | sf::Style::Close);

    window.setFramerateLimit(200);

    if (!iconImage.loadFromFile(ICON_PATH))
    {
        std::cout << "ERROR: Cannot load window icon" << std::endl;
        return false;
    }
    window.setIcon(iconImage.getSize(), iconImage.getPixelsPtr());

    if (!TextureManager::loadTextures())
    {
        std::cout << "ERROR: Textures have not been loaded correctly" << std::endl;
        return false;
    }

    if (!TextRenderer::loadFont(FONT_PATH))
    {
        std::cout << "ERROR: Font has not been loaded correctly" << std::endl;
        return false;
    }

    mainPlanetRenderer.setPosition(sf::Vector2f(1700, 1700));
    mainPlanetRenderer.setScale(6);

    return true;

}

void Game::mainLoop()
{

    Camera::setOffset(sf::Vector2f(900, 900));

    playerShip.setPosition(sf::Vector2f(1500, 1500));

    for (int i = 0; i < 50; i++)
    {
        sf::Vector2f position(rand() % 3000, rand() % 3000);
        AsteroidManager::createAsteroid(position);
    }

    while (window.isOpen())
    {

        // Event handling
        
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }

        }

        

        // Logic

        float deltaTime = clock.restart().asSeconds();

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        playerShip.update(deltaTime, mousePosition);

        BulletManager::updateBullets(deltaTime);

        AsteroidManager::updateAsteroids(deltaTime);

        mainPlanetRenderer.update(deltaTime);

        Camera::update(playerShip.getPosition(), deltaTime);



        // Render

        window.clear();

        sf::Vector2f drawOffset = Camera::getDrawOffset();

        TextureDrawData backgroundData = {TextureType::EarthBackground, sf::Vector2f(drawOffset.x / 2, drawOffset.y / 2), sf::degrees(0), 3, false};
        TextureManager::drawSubTexture(window, backgroundData, sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(WORLD_WIDTH, WORLD_HEIGHT)));

        mainPlanetRenderer.draw(window);

        ItemPickupManager::drawPickups(window);

        AsteroidManager::drawAsteroids(window);

        BulletManager::drawBullets(window);

        playerShip.draw(window);



        // UI

        std::string text = std::to_string(static_cast<int>(1 / deltaTime)) + " FPS";
        TextRenderer::drawText(window, {text, sf::Vector2f(20, 10), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3});

        text = std::to_string(BulletManager::getBulletCount()) + " Bullets";
        TextRenderer::drawText(window, {text, sf::Vector2f(20, 70), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3});

        text = std::to_string(AsteroidManager::getAsteroids().size()) + " Asteroids";
        TextRenderer::drawText(window, {text, sf::Vector2f(20, 130), sf::Color(255, 255, 255), 60, sf::Color(0, 0, 0), 3});



        window.display();

    }

}
