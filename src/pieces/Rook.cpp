#include "Rook.hpp"
#include "../shared/config/Board.hpp"

std::vector<sf::Vector2i> Rook::getLegalMoves() const
{
    std::vector<sf::Vector2i> moves;

    const std::vector<sf::Vector2i> directions = {
        {0, -1}, // Up
        {0, 1},  // Down
        {-1, 0}, // Left
        {1, 0},  // Right
    };

    for(const auto &dir : directions)
    {
        int i = 1;
        while(true)
        {
            sf::Vector2i newPosition = {currentPosition.x + dir.x * i,
                                        currentPosition.y + dir.y * i};

            if(newPosition.x < 0 || newPosition.x >= BoardConfig::GridSize ||
               newPosition.y < 0 || newPosition.y >= BoardConfig::GridSize)
            {
                break;
            }

            moves.push_back(newPosition);
            i++;
        }
    }

    return moves;
};
