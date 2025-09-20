#include "Queen.hpp"
#include "../config/Board.hpp"

std::vector<sf::Vector2i> Queen::getLegalMoves() const
{
    std::vector<sf::Vector2i> moves;

    const std::vector<sf::Vector2i> directions = {
        {0, -1},  // Up
        {0, 1},   // Down
        {-1, 0},  // Left
        {1, 0},   // Right
        {-1, -1}, // Top-left (diagonal up-left)
        {1, -1},  // Top-right (diagonal up-right)
        {-1, 1},  // Bottom-left (diagonal down-left)
        {1, 1}    // Bottom-right (diagonal down-right)
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
}

std::vector<sf::Vector2i> Queen::getValidMoves(Board &board) const
{
    std::vector<sf::Vector2i> moves;
    return moves;
}
