#pragma once

#include "shared/GameData.hpp"
#include "shared/Move.hpp"
#include "shared/Time.hpp"
#include <chrono>
#include <memory>
#include <vector>

struct GameState
{
    Side currentSide = Side::White;
    GamePreset preset = GamePresets::Rapid::_10min;
    unsigned int fiftyMoveCounter = 50;
    bool isDragging = false;
    bool isPlaying = false;
    bool hasGameStarted = false;

    Timer whiteTimer;
    Timer blackTimer;

    std::vector<std::unique_ptr<Move>> moves = {};

    // TODO: consider changing to shared_ptr
    std::shared_ptr<Piece> selectedPiece = nullptr;

    void addMove(std::unique_ptr<Move> move);
    void onGameStart();
    void decrementTimeForCurrentSide(std::chrono::milliseconds value);
    void incrementTimeForCurrentSide();
    void initializeTimers();
    void nextSide();
    void print();
    Timer &getCurrentTimer();
};
