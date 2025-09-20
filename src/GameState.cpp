#include "GameState.hpp"
#include "GameData.hpp"
#include "Notation.hpp"
#include <chrono>
#include <iostream>

void GameState::addMove(std::unique_ptr<Move> move)
{
    if(!hasGameStarted)
    {
        hasGameStarted = true;
        onGameStart();
    }
    moves.push_back(std::move(move));
}

void GameState::onGameStart()
{
    initializeTimers();
    // ...
}

void GameState::decrementTimeForCurrentSide(std::chrono::milliseconds value)
{
    Timer &currentTimer = getCurrentTimer();
    currentTimer.decrement(value);

    if(currentTimer.millis == 0ms)
    {
        isPlaying = false;
        std::cout << "Game over, " << StringUtils::toString(currentSide)
                  << " lost!\n";
    }
}

void GameState::incrementTimeForCurrentSide()
{
    getCurrentTimer().increment(preset.timeControl->increment);
}

void GameState::initializeTimers()
{
    whiteTimer.millis = preset.timeControl->duration;
    blackTimer.millis = preset.timeControl->duration;
};

void GameState::nextSide()
{
    currentSide = (currentSide == Side::White) ? Side::Black : Side::White;
}

Timer &GameState::getCurrentTimer()
{
    return (currentSide == Side::White) ? whiteTimer : blackTimer;
}

void GameState::print()
{
    std::cout << "Current side: " << StringUtils::toString(currentSide) << "\n";

    if(selectedPiece)
    {
        std::cout << "Selected piece: "
                  << StringUtils::toString(selectedPiece->getKind()) << "\n";
    }

    std::cout << "White remaining seconds: " << whiteTimer.millis / 1000 << "\n"
              << "Black remaining seconds: " << blackTimer.millis / 1000
              << "\n";

    std::cout << (!moves.empty() ? "Moves:\n" : "");
    for(int i = 0; i < moves.size(); i++)
    {
        auto &move = moves[i];

        std::cout << i << ". " << StringUtils::toString(move->piece.getSide())
                  << " " << StringUtils::toString(move->piece.getKind())
                  << " moved from " << Notation::toChessNotation(move->from)
                  << " to " << Notation::toChessNotation(move->to)
                  << " and captured "
                  << (move->captured.has_value()
                          ? StringUtils::toString(move->captured.value())
                          : "nothing")
                  << ".\n";
    }
}
