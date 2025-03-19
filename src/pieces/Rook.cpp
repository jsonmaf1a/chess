#include "Rook.hpp"

// TODO:
// * Blocking by other pieces
// * Castle
std::vector<sf::Vector2i> Rook::getLegalMoves(
    std::vector<std::shared_ptr<Piece>> onBoard) const
{
    std::vector<sf::Vector2i> moves;

    sf::Vector2i position(currentPosition);

    // Up
    for(int i = 1; currentPosition.y - i >= 0; i++)
    {
        moves.push_back({position.x, position.y - i});
    }

    // Down
    for(int i = 1; currentPosition.y + i < 8; i++)
    {
        moves.push_back({position.x, position.y + i});
    }

    // Left
    for(int i = 1; currentPosition.x - i >= 0; i++)
    {
        moves.push_back({position.x - i, position.y});
    }

    // Right
    for(int i = 1; currentPosition.x + i < 8; i++)
    {
        moves.push_back({position.x + i, position.y});
    }

    return moves;
};
