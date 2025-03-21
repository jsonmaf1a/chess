#pragma once

#include "shared/GameData.hpp"
#include "shared/Move.hpp"
#include <memory>
#include <vector>

struct GameState
{
    unsigned int fiftyMoveCounter;
    Side currentSide;
    bool isStarted;
    GameModePreset preset;

    std::vector<std::unique_ptr<Move>> moves = {};
    std::optional<std::reference_wrapper<Piece>> selectedPiece = std::nullopt;
};
