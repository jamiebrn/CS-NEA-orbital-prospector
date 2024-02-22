#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

#include <SFML/Audio.hpp>
#include <PhysFsStream.hpp>

#include <unordered_map>
#include <string>
#include <memory>

#include "Renderer/TextRenderer.hpp"
#include "Constants.hpp"

enum class SoundType
{
    Shoot,
    EnemyShoot,
    AsteroidExplode,
    ShipExplode,
    ItemPickup,
    Coins,
    Forge
};

enum class MusicType
{
    Menu,
    Track1
};

class SoundManager
{

private:
    SoundManager() = delete;

public:
    static bool loadSounds(sf::RenderWindow& window);

    static void playSound(SoundType type);

    static void playMusic(MusicType type);

    static void stopMusic(MusicType type);

private:
    inline static bool loadedSounds = false;

    inline static std::unordered_map<SoundType, sf::SoundBuffer> soundBufferMap;

    inline static std::unordered_map<SoundType, sf::Sound> soundMap;

    inline static const std::unordered_map<SoundType, std::string> soundPaths = {
        {SoundType::Shoot, "Data/Sfx/shoot.wav"},
        {SoundType::EnemyShoot, "Data/Sfx/enemyShoot.wav"},
        {SoundType::AsteroidExplode, "Data/Sfx/asteroidExplode.wav"},
        {SoundType::ShipExplode, "Data/Sfx/shipExplosion.wav"},
        {SoundType::ItemPickup, "Data/Sfx/itemPickup.wav"},
        {SoundType::Coins, "Data/Sfx/coins.wav"},
        {SoundType::Forge, "Data/Sfx/forge.wav"}
    };

    inline static std::unordered_map<MusicType, PhysFsStream> musicStreamMap;

    inline static std::unordered_map<MusicType, std::unique_ptr<sf::Music>> musicMap;

    static constexpr float MUSIC_VOLUME = 10.0f;

    inline static const std::unordered_map<MusicType, std::string> musicPaths = {
        {MusicType::Menu, "Data/Music/Mystery.mp3"},
        {MusicType::Track1, "Data/Music/Arthur Vyncke - A few jumps away.mp3"}
    };

};

#endif