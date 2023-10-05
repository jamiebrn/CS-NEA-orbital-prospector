#include "Manager/SoundManager.hpp"

bool SoundManager::loadSounds()
{
    if (loadedSounds)
        return true;
    
    loadedSounds = true;

    for (std::pair<SoundType, std::string> soundPair : soundPaths)
    {
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
    }

    for (std::pair<MusicType, std::string> musicPair : musicPaths)
    {

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