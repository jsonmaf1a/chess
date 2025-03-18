#include "Rook.hpp"

// TODO:
// * Blocking by other pieces
// * Castle
std::vector<sf::Vector2i> Rook::getLegalMoves() const
{
    std::vector<sf::Vector2i> moves;

    // Up
    for(int i = 1; currentPosition.y - i >= 0; i++)
    {
        moves.push_back({currentPosition.x, currentPosition.y - i});
    }

    // Down
    for(int i = 1; currentPosition.y + i < 8; i++)
    {
        moves.push_back({currentPosition.x, currentPosition.y + i});
    }

    // Left
    for(int i = 1; currentPosition.x - i >= 0; i++)
    {
        moves.push_back({currentPosition.x - i, currentPosition.y});
    }

    // Right
    for(int i = 1; currentPosition.x + i < 8; i++)
    {
        moves.push_back({currentPosition.x + i, currentPosition.y});
    }

    return moves;
};
