#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <SFML/Audio.hpp>

#include <unordered_map>
#include <string>
#include <memory>

enum class SoundType
{
    Shoot,
    AsteroidExplode,
    ItemPickup
};

enum class MusicType
{
    Track1
};

class SoundManager
{

private:
    SoundManager() = delete;

public:
    static bool loadSounds();

    static void playSound(SoundType type);

    static void playMusic(MusicType type);

private:
    inline static bool loadedSounds = false;

    inline static std::unordered_map<SoundType, sf::SoundBuffer> soundBufferMap;

    inline static std::unordered_map<SoundType, sf::Sound> soundMap;

    inline static const std::unordered_map<SoundType, std::string> soundPaths = {
        {SoundType::Shoot, "Sfx/shoot.wav"},
        {SoundType::AsteroidExplode, "Sfx/asteroidExplode.wav"},
        {SoundType::ItemPickup, "Sfx/itemPickup.wav"}
    };

    inline static std::unordered_map<MusicType, std::unique_ptr<sf::Music>> musicMap;

    static constexpr float MUSIC_VOLUME = 15.0f;

    inline static const std::unordered_map<MusicType, std::string> musicPaths = {
        {MusicType::Track1, "Music/Arthur Vyncke - A few jumps away.flac"}
    };

};

#endif