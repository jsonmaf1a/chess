#include "Rook.hpp"

// TODO:
// * Blocking by other pieces
// * Castle
std::vector<sf::Vector2i> Rook::getValidMoves() const
{
    std::vector<sf::Vector2i> moves;

    // Up
    for(int i = 1; position.y - i >= 0; i++)
    {
        moves.push_back({position.x, position.y - i});
    }

    // Down
    for(int i = 1; position.y + i < 8; i++)
    {
        moves.push_back({position.x, position.y + i});
    }

    // Left
    for(int i = 1; position.x - i >= 0; i++)
    {
        moves.push_back({position.x - i, position.y});
    }

    // Right
    for(int i = 1; position.x + i < 8; i++)
    {
        moves.push_back({position.x + i, position.y});
    }

    return moves;
};
