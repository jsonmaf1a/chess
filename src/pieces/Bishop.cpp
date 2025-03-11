#include "Bishop.hpp"

// TODO:
// * Blocking by other pieces
std::vector<sf::Vector2i> Bishop::getValidMoves() const
{
    std::vector<sf::Vector2i> moves;

    // Top-left (diagonal up-left)
    for(int i = 1; position.x - i >= 0 && position.y - i >= 0; i++)
    {
        moves.push_back({position.x - i, position.y - i});
    }

    // Top-right (diagonal up-right)
    for(int i = 1; position.x + i < 8 && position.y - i >= 0; i++)
    {
        moves.push_back({position.x + i, position.y - i});
    }

    // Bottom-left (diagonal down-left)
    for(int i = 1; position.x - i >= 0 && position.y + i < 8; i++)
    {
        moves.push_back({position.x - i, position.y + i});
    }

    // Bottom-right (diagonal down-right)
    for(int i = 1; position.x + i < 8 && position.y + i < 8; i++)
    {
        moves.push_back({position.x + i, position.y + i});
    }

    return moves;
};
