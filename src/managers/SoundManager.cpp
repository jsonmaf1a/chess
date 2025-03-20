#include "SoundManager.hpp"
#include <iostream>

namespace
{
    static std::unordered_map<SoundKind, std::shared_ptr<sf::SoundBuffer>>
        soundBuffers;
    static std::vector<sf::Sound> activeSounds;
} // namespace

namespace SoundManager
{
    void loadSounds()
    {
        const std::string BASE_PATH = "assets/audio/";

        std::unordered_map<SoundKind, std::string> soundPaths = {
            {SoundKind::Capture, "capture.mp3"},
            {SoundKind::Castle, "castle.mp3"},
            {SoundKind::GameEnd, "game-end.mp3"},
            {SoundKind::GameStart, "game-start.mp3"},
            {SoundKind::IllegalMove, "illegal.mp3"},
            {SoundKind::MoveCheck, "move-check.mp3"},
            {SoundKind::MoveSelf, "move-self.mp3"},
            {SoundKind::MoveOpponent, "move-opponent.mp3"},
            {SoundKind::Premove, "premove.mp3"},
            {SoundKind::Promote, "promote.mp3"},
            {SoundKind::TenSecondsLeft, "tenseconds.mp3"},
        };

        for(const auto &[soundKind, soundPath] : soundPaths)
        {
            auto buf = std::make_shared<sf::SoundBuffer>();
            if(!buf->loadFromFile(BASE_PATH + soundPath))
                throw std::runtime_error("Failed to load sound: " + BASE_PATH +
                                         soundPath);

            soundBuffers.insert({soundKind, buf});
        }
    }

    void playSound(SoundKind kind)
    {
        if(soundBuffers.find(kind) != soundBuffers.end())
        {
            auto buf = soundBuffers.at(kind);

            activeSounds.emplace_back(*buf);
            sf::Sound &sound = activeSounds.back();
            sound.setVolume(100.f);
            sound.play();

            if(sound.getStatus() != sf::Sound::Status::Playing)
            {
                std::cout << "Sound failed to play: " << soundKindToString(kind)
                          << std::endl;
            }
        }
        else
        {
            std::cout << "Sound not found: " << soundKindToString(kind)
                      << std::endl;
        }
    }

    void cleanupFinishedSounds()
    {
        activeSounds.erase(std::remove_if(activeSounds.begin(),
                                          activeSounds.end(),
                                          [](const sf::Sound &sound) {
                                              return sound.getStatus() ==
                                                     sf::Sound::Status::Stopped;
                                          }),
                           activeSounds.end());
    }

    const char *soundKindToString(SoundKind kind)
    {
        switch(kind)
        {
            case SoundKind::GameEnd:
                return "GameEnd";
            case SoundKind::GameStart:
                return "GameStart";
            case SoundKind::IllegalMove:
                return "IllegalMove";
            case SoundKind::MoveCheck:
                return "MoveCheck";
            case SoundKind::MoveOpponent:
                return "MoveOpponent";
            case SoundKind::MoveSelf:
                return "MoveSelf";
            case SoundKind::Premove:
                return "Premove";
            case SoundKind::Capture:
                return "Capture";
            case SoundKind::Castle:
                return "Castle";
            case SoundKind::Promote:
                return "Promote";
            case SoundKind::TenSecondsLeft:
                return "TenSecondsLeft";
            default:
                return "Unknown";
        }
    }
} // namespace SoundManager
