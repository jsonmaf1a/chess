#include "Pawn.hpp"

// TODO:
// * Capturing diagonally
// * En passant
// * Blocking by other pieces
// * Pawn promotion
std::vector<sf::Vector2i> Pawn::getValidMoves() const
{
    std::vector<sf::Vector2i> moves;

    int direction = (side == Side::White) ? -1 : 1;

    int newY = currentPosition.y + direction;
    if(newY >= 0 && newY < 8)
    {
        moves.push_back({currentPosition.x, newY});
    }

    if(!wasMoved)
    {
        int newY = currentPosition.y + 2 * direction;
        if(newY >= 0 && newY < 8)
        {
            moves.push_back({currentPosition.x, newY});
        }
    }

    return moves;
};
