#include "King.hpp"
#include "../shared/config/Board.hpp"

std::vector<sf::Vector2i> King::getLegalMoves() const
{
    std::vector<sf::Vector2i> moves;

    int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                            {0, 1},   {1, -1}, {1, 0},  {1, 1}};

    // Loop through all possible moves
    for(int i = 0; i < BoardConfig::GridSize; i++)
    {
        int newX = currentPosition.x + directions[i][0];
        int newY = currentPosition.y + directions[i][1];

        moves.push_back({newX, newY});
    }

    return moves;
};

std::vector<sf::Vector2i> King::getValidMoves(Board &board) const
{
    std::vector<sf::Vector2i> moves;
    return moves;
}
