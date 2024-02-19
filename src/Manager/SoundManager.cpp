#include "Manager/SoundManager.hpp"

bool SoundManager::loadSounds(sf::RenderWindow& window)
{
    if (loadedSounds)
        return true;
    
    loadedSounds = true;

    TextDrawData loadText = {
        "Loading sounds",
        sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
        sf::Color(255, 255, 255),
        32,
        sf::Color(0, 0, 0),
        4,
        true,
        true
    };

    float soundsLoaded = 0;
    for (std::pair<SoundType, std::string> soundPair : soundPaths)
    {
        window.clear();

        std::string text = "Orbital Prospector";
        TextRenderer::drawText(window, {text, sf::Vector2f(WINDOW_WIDTH / 2, 150), sf::Color(255, 255, 255), 130, sf::Color(0, 0, 0), 4, true});

        loadText.text = "Loading sounds (" + std::to_string(static_cast<int>((soundsLoaded / (soundPaths.size() + musicPaths.size())) * 100)) + "%)";
        TextRenderer::drawText(window, loadText);

        window.display();

        SoundType soundType = soundPair.first;
        std::string soundPath = soundPair.second;

        sf::SoundBuffer soundBuffer;
        if (!soundBuffer.loadFromFile(soundPath))
        {
            loadedSounds = false;
            break;
        }

        soundBufferMap[soundType] = soundBuffer;

        sf::Sound sound;
        sound.setBuffer(soundBufferMap[soundType]);

        soundMap[soundType] = sound;

        soundsLoaded++;
    }

    for (std::pair<MusicType, std::string> musicPair : musicPaths)
    {

        window.clear();

        std::string text = "Orbital Prospector";
        TextRenderer::drawText(window, {text, sf::Vector2f(WINDOW_WIDTH / 2, 150), sf::Color(255, 255, 255), 130, sf::Color(0, 0, 0), 4, true});

        loadText.text = "Loading sounds (" + std::to_string(static_cast<int>((soundsLoaded / (soundPaths.size() + musicPaths.size()) * 100))) + "%)";
        TextRenderer::drawText(window, loadText);
        
        window.display();

        MusicType musicType = musicPair.first;
        std::string musicPath = musicPair.second;

        std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();
        if (!music->openFromFile(musicPath))
        {
            loadedSounds = false;
            break;
        }

        music->setLoop(true);
        music->setVolume(MUSIC_VOLUME);

        musicMap[musicType] = std::move(music);

        soundsLoaded++;
    }

    if (!loadedSounds)
        return false;
    
    return true;
}

void SoundManager::playSound(SoundType type)
{
    if (!loadedSounds)
        return;

    soundMap.at(type).play();
}

void SoundManager::playMusic(MusicType type)
{
    if (!loadedSounds)
        return;
    
    for (auto& music : musicMap)
    {
        music.second->stop();
    }
    
    musicMap.at(type)->play();
}

void SoundManager::stopMusic(MusicType type)
{
    if (!loadedSounds)
        return;
    
    musicMap.at(type)->stop();
}