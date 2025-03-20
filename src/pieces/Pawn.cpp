#include "Pawn.hpp"
#include "../shared/config/Board.hpp"

std::vector<sf::Vector2i> Pawn::getLegalMoves() const
{
    std::vector<sf::Vector2i> moves;

    int direction = (side == Side::White) ? -1 : 1;

    int newY = currentPosition.y + direction;
    if(newY >= 0 && newY < BoardConfig::GridSize)
    {
        moves.push_back({currentPosition.x, newY});

        int newX = currentPosition.x + 1;
        if(newX < BoardConfig::GridSize)
            moves.push_back({newX, newY});

        newX = currentPosition.x - 1;
        if(newX >= 0)
            moves.push_back({newX, newY});
    }

    if(!wasMoved)
    {
        int newY = currentPosition.y + 2 * direction;
        if(newY >= 0 && newY < BoardConfig::GridSize)
        {
            moves.push_back({currentPosition.x, newY});
        }
    }

    return moves;
};
