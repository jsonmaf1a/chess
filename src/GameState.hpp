#pragma once

#include "shared/GameData.hpp"
#include "shared/Move.hpp"
#include <iostream>
#include <memory>
#include <vector>

struct Timer
{
    int millis = 0;

    void decrement(unsigned int value)
    {
        if(millis <= value)
        {
            millis = 0;
        }
        else
        {
            millis -= value;
        }
    }

    void increment(int value) { millis += value; }
};

struct GameState
{
    unsigned int fiftyMoveCounter;
    Side currentSide;
    bool isPlaying;
    GameModePreset preset;

    Timer whiteTimer;
    Timer blackTimer;

    std::vector<std::unique_ptr<Move>> moves = {};
    std::optional<std::reference_wrapper<Piece>> selectedPiece = std::nullopt;

    void decrementTimeForCurrentSide(unsigned int value)
    {
        Timer &currentTimer =
            (currentSide == Side::White) ? whiteTimer : blackTimer;

        currentTimer.decrement(value);

        if(currentTimer.millis == 0)
        {
            isPlaying = false;
            std::cout << "Game over, someone lost!";
        }
    }

    void incrementTimeForCurrentSide()
    {
        Timer &currentTimer =
            (currentSide == Side::White) ? whiteTimer : blackTimer;
        currentTimer.increment(preset.timeControl->incrementMillis);
    }

    void initializeClocks()
    {
        whiteTimer.millis = preset.timeControl->millis;
        blackTimer.millis = preset.timeControl->millis;
    };

    void nextSide()
    {
        currentSide = currentSide == Side::White ? Side::Black : Side::White;
    }

    void print()
    {
        std::cout << "Current side: " << StringUtils::toString(currentSide)
                  << "\n";

        if(selectedPiece.has_value())
        {
            std::cout << "Selected piece: "
                      << selectedPiece.value().get().getStringifiedKind()
                      << "\n";
        }

        std::cout << "White remaining seconds: " << whiteTimer.millis / 1000
                  << "\n"
                  << "Black remaining seconds: " << blackTimer.millis / 1000
                  << "\n";

        std::cout << !moves.empty() && "Moves:\n";
        for(int i = 0; i < moves.size(); i++)
        {
            auto &move = moves[i];

            std::cout << i << ". "
                      << StringUtils::toString(move->piece.getSide()) << " "
                      << move->piece.getStringifiedKind() << " moved from ["
                      << move->from.x << move->from.y << "] to [" << move->to.x
                      << move->to.y << "] "
                      << "and captured "
                      << (move->captured
                              ? StringUtils::toString(move->captured.value())
                              : "nothing")
                      << ".\n";
        }
    }
};
