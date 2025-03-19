#include "Bishop.hpp"
#include <cmath>

// TODO:
// * Blocking by other pieces
std::vector<sf::Vector2i> Bishop::getLegalMoves(
    std::vector<std::shared_ptr<Piece>> onBoard) const
{
    std::vector<sf::Vector2i> moves;

    // Top-left (diagonal up-left)
    for(int i = 1; currentPosition.x - i >= 0 && currentPosition.y - i >= 0;
        i++)
    {
        moves.push_back({currentPosition.x - i, currentPosition.y - i});
    }

    // Top-right (diagonal up-right)
    for(int i = 1; currentPosition.x + i < 8 && currentPosition.y - i >= 0; i++)
    {
        moves.push_back({currentPosition.x + i, currentPosition.y - i});
    }

    // Bottom-left (diagonal down-left)
    for(int i = 1; currentPosition.x - i >= 0 && currentPosition.y + i < 8; i++)
    {
        moves.push_back({currentPosition.x - i, currentPosition.y + i});
    }

    // Bottom-right (diagonal down-right)
    for(int i = 1; currentPosition.x + i < 8 && currentPosition.y + i < 8; i++)
    {
        moves.push_back({currentPosition.x + i, currentPosition.y + i});
    }

    return moves;
};
