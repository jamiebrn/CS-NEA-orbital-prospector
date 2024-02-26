// SoundManager.cpp

#include "Manager/SoundManager.hpp"

// Load all sounds into memory (sound effects and music)
bool SoundManager::loadSounds(sf::RenderWindow& window)
{
    // If sound have already been loaded, return true by default
    if (loadedSounds)
        return true;
    
    // Set loaded sounds to true by default
    loadedSounds = true;

    // Create text object for load screen progress display
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

    // Count of loaded sounds (uses float in order to perform float division, rather than casting from int to flat)
    float soundsLoaded = 0;

    // Iterate over every sound effect and its file path, and attempt to load it
    for (std::pair<SoundType, std::string> soundPair : soundPaths)
    {

        // Load screen
        // Clear window
        window.clear();

        // Draw title at top-centre of screen
        std::string text = "Orbital Prospector";
        TextRenderer::drawText(window, {text, sf::Vector2f(WINDOW_WIDTH / 2, 150), sf::Color(255, 255, 255), 130, sf::Color(0, 0, 0), 4, true});

        // Draw progress of loading sounds
        loadText.text = "Loading sounds (" + std::to_string(static_cast<int>((soundsLoaded / (soundPaths.size() + musicPaths.size())) * 100)) + "%)";
        TextRenderer::drawText(window, loadText);

        // Update window with new data
        window.display();

        // Get sound type and file path from map
        SoundType soundType = soundPair.first;
        std::string soundPath = soundPair.second;

        // Create stream object to load data from disk
        PhysFsStream soundStream;

        // If cannot load file at file path into stream, set loaded sounds to false and stop loading
        if (!soundStream.open(soundPath.c_str()))
        {
            // Set loaded sounds to false
            loadedSounds = false;
            // Stop loading
            break;
        }

        // Create sound buffer object to store file stream data
        sf::SoundBuffer soundBuffer;

        // Load sound data from file stream - set loaded sound to false and stop loading if failed
        if (!soundBuffer.loadFromStream(soundStream))
        {
            // Set loaded sounds to false
            loadedSounds = false;
            // Stop loading
            break;
        }

        // Store sound buffer in map
        soundBufferMap[soundType] = soundBuffer;

        // Create a sound object to interface with the sound buffer
        sf::Sound sound;
        // Set the buffer object of the sound object to the sound buffer in the map
        sound.setBuffer(soundBufferMap[soundType]);

        // Store sound object in map
        soundMap[soundType] = sound;

        // Increment sounds loaded count
        soundsLoaded++;
    }

    // Iterate over every music track and its file path, and attempt to load it
    for (std::pair<MusicType, std::string> musicPair : musicPaths)
    {

        // Load screen
        // Clear window
        window.clear();

        // Draw title at top-centre of screen
        std::string text = "Orbital Prospector";
        TextRenderer::drawText(window, {text, sf::Vector2f(WINDOW_WIDTH / 2, 150), sf::Color(255, 255, 255), 130, sf::Color(0, 0, 0), 4, true});

        // Draw progress of loading sounds
        loadText.text = "Loading sounds (" + std::to_string(static_cast<int>((soundsLoaded / (soundPaths.size() + musicPaths.size()) * 100))) + "%)";
        TextRenderer::drawText(window, loadText);
        
        // Update window with new data
        window.display();

        // Get music type and file path from map
        MusicType musicType = musicPair.first;
        std::string musicPath = musicPair.second;

        // Construct a new stream object in-place in the map
        // Must be done in-place as with music objects, the data stream must be kept open at runtime.
        // If a stream is created and copied, the original object will be destroyed, calling its destructor
        // and therefore freeing the memory which the stream is pointing too (the music).
        musicStreamMap.emplace(musicType, PhysFsStream());

        // Get the stream object from the map and attempt to open music at the file path
        if (!musicStreamMap.at(musicType).open(musicPath.c_str()))
        {
            // If failed, set loaded sounds to false
            loadedSounds = false;
            // Stop loading music
            break;
        }

        // Create music object (on heap as music object is non-copyable)
        std::unique_ptr<sf::Music> music = std::make_unique<sf::Music>();

        // Attempt to load the music stream object into the music object
        if (!music->openFromStream(musicStreamMap.at(musicType)))
        {
            // If failed, set loaded sounds to false
            loadedSounds = false;
            // Stop loading music
            break;
        }

        // Enable music looping and set volume
        music->setLoop(true);
        music->setVolume(MUSIC_VOLUME);

        // Move music pointer into map (must be moved as is a unique_ptr, i.e. cannot be copied)
        musicMap[musicType] = std::move(music);

        // Increment sounds loaded
        soundsLoaded++;
    }

    // If loaded sounds is false (unsuccessful load), return false
    if (!loadedSounds)
        return false;
    
    // Return true by default
    return true;
}

// Unload all sounds from memory
void SoundManager::unloadSounds()
{
    // Set loaded sounds to false, as they are about to be unloaded
    loadedSounds = false;

    // Delete all sound objects
    soundMap.clear();
    // Delete all sound buffers (must be deleted after sound objects)
    soundBufferMap.clear();

    // Delete all music objects
    musicMap.clear();
    // Delete all music streams (must be deleted after music objects)
    musicStreamMap.clear();
}

// Play sound effect
void SoundManager::playSound(SoundType type)
{
    // If sounds have not been loaded, return by default
    if (!loadedSounds)
        return;

    // Play sound from sound map
    soundMap.at(type).play();
}

// Play music track
void SoundManager::playMusic(MusicType type)
{
    // If sounds have not been loaded, return by default
    if (!loadedSounds)
        return;
    
    // Stop all music tracks
    for (auto& music : musicMap)
    {
        music.second->stop();
    }
    
    // Play music track from map
    musicMap.at(type)->play();
}

// Stop music track
void SoundManager::stopMusic(MusicType type)
{
    // If sounds have not been loaded, return by default
    if (!loadedSounds)
        return;
    
    // Stop music track from map
    musicMap.at(type)->stop();
}