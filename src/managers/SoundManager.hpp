#pragma once

#include <SFML/Audio.hpp>

enum class SoundKind
{
    GameEnd,
    GameStart,
    IllegalMove,
    MoveCheck,
    MoveOpponent,
    MoveSelf,
    Premove,
    Capture,
    Castle,
    Promote,
    TenSecondsLeft,
};

namespace SoundManager
{
    void loadSounds();
    sf::SoundBuffer loadSoundBuffer(std::string path);
    void playSound(SoundKind sound);
    void cleanupFinishedSounds();
    const char *soundKindToString(SoundKind sound);
} // namespace SoundManager
