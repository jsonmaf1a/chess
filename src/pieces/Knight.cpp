#include "Knight.hpp"
#include "../shared/config/Board.hpp"

std::vector<sf::Vector2i> Knight::getLegalMoves() const
{
    std::vector<sf::Vector2i> moves;

    std::vector<sf::Vector2i> positions = {{2, 1}, {2, -1}, {-2, 1}, {-2, -1},
                                           {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

    for(const auto &pos : positions)
    {
        int newX = currentPosition.x + pos.x;
        int newY = currentPosition.y + pos.y;

        if(newX >= 0 && newX < BoardConfig::GridSize && newY >= 0 &&
           newY < BoardConfig::GridSize)
        {
            moves.push_back({newX, newY});
        }
    }

    return moves;
}
