// SoundManager.hpp

#ifndef SOUND_MANAGER_HPP
#define SOUND_MANAGER_HPP

// Include libraries
#include <SFML/Audio.hpp>
#include <PhysFsStream.hpp>
#include <unordered_map>
#include <string>
#include <memory>

// Include headers
#include "Renderer/TextRenderer.hpp"
#include "Constants.hpp"

// Enum containing all sound effects
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

// Enum containing all music tracks
enum class MusicType
{
    Menu,
    Track1
};

// Declare sound manager class
class SoundManager
{

// Delete constructor, as is static class
private:
    SoundManager() = delete;

// Public class functions
public:
    // Load all sounds into memory (sound effects and music)
    static bool loadSounds(sf::RenderWindow& window);

    // Unload all sounds from memory
    static void unloadSounds();

    // Play sound effect
    static void playSound(SoundType type);

    // Play music track
    static void playMusic(MusicType type);

    // Stop music track
    static void stopMusic(MusicType type);

// Private member variables
private:
    // Variable keeping track of whether sounds are loaded into memory
    inline static bool loadedSounds = false;

    // Map storing buffers, which store sound effect data
    inline static std::unordered_map<SoundType, sf::SoundBuffer> soundBufferMap;

    // Map storing sound objects which interface the sound buffers
    inline static std::unordered_map<SoundType, sf::Sound> soundMap;

    // Constant map storing file paths for all sound effects
    inline static const std::unordered_map<SoundType, std::string> soundPaths = {
        {SoundType::Shoot, "Sfx/shoot.wav"},
        {SoundType::EnemyShoot, "Sfx/enemyShoot.wav"},
        {SoundType::AsteroidExplode, "Sfx/asteroidExplode.wav"},
        {SoundType::ShipExplode, "Sfx/shipExplosion.wav"},
        {SoundType::ItemPickup, "Sfx/itemPickup.wav"},
        {SoundType::Coins, "Sfx/coins.wav"},
        {SoundType::Forge, "Sfx/forge.wav"}
    };

    // Map storing stream objects, which store music data
    inline static std::unordered_map<MusicType, PhysFsStream> musicStreamMap;

    // Map storing music objects, which interface with the music streams
    inline static std::unordered_map<MusicType, std::unique_ptr<sf::Music>> musicMap;

    // Constant storing volume of music
    static constexpr float MUSIC_VOLUME = 10.0f;

    // Constant map storing file paths for all music tracks
    inline static const std::unordered_map<MusicType, std::string> musicPaths = {
        {MusicType::Menu, "Music/Mystery.mp3"},
        {MusicType::Track1, "Music/Arthur Vyncke - A few jumps away.mp3"}
    };

};

#endif