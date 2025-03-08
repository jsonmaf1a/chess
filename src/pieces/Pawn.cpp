#include "Pawn.hpp"

#include <vector>

// TODO:
// * Capturing diagonally
// * En passant
// * Blocking by other pieces
// * Pawn promotion
std::vector<sf::Vector2i> Pawn::getValidMoves() const
{
    std::vector<sf::Vector2i> moves;
    int direction = (color == PieceColor::White) ? -1 : 1;

    int newY = position.y + direction;
    if(newY >= 0 && newY < 8)
    {
        moves.push_back({position.x, newY});
    }

    if(isInInitialPosition())
    {
        int newY = position.y + 2 * direction;
        if(newY >= 0 && newY < 8)
        {
            moves.push_back({position.x, newY});
        }
    }

    return moves;
};
