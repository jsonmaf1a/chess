#include "pieces/Pawn.hpp"
#include "shared/config/Board.hpp"

// std::vector<sf::Vector2i> Pawn::getLegalMoves() const
// {
//     std::vector<sf::Vector2i> moves;
//
//     int direction = (side == Side::White) ? -1 : 1;
//
//     int newY = currentPosition.y + direction;
//     if(newY >= 0 && newY < BoardConfig::GridSize)
//     {
//         moves.push_back({currentPosition.x, newY});
//
//         int newX = currentPosition.x + 1;
//         if(newX < BoardConfig::GridSize)
//             moves.push_back({newX, newY});
//
//         newX = currentPosition.x - 1;
//         if(newX >= 0)
//             moves.push_back({newX, newY});
//     }
//
//     if(!wasMoved)
//     {
//         int newY = currentPosition.y + 2 * direction;
//         if(newY >= 0 && newY < BoardConfig::GridSize)
//         {
//             moves.push_back({currentPosition.x, newY});
//         }
//     }
//
//     return moves;
// };

std::vector<sf::Vector2i> Pawn::getLegalMoves() const
{
    std::vector<sf::Vector2i> moves;
    int direction = (side == Side::White) ? -1 : 1;

    // Forward move (only if not blocked)
    sf::Vector2i oneStep = {currentPosition.x, currentPosition.y + direction};
    if(oneStep.y >= 0 && oneStep.y < BoardConfig::GridSize)
        moves.push_back(oneStep);

    // Two-square move from the start position
    if(!hasMoved)
    {
        sf::Vector2i twoSteps = {currentPosition.x,
                                 currentPosition.y + 2 * direction};
        if(twoSteps.y >= 0 && twoSteps.y < BoardConfig::GridSize)
            moves.push_back(twoSteps);
    }

    // Capture diagonally (left and right)
    sf::Vector2i captureLeft = {currentPosition.x - 1,
                                currentPosition.y + direction};
    sf::Vector2i captureRight = {currentPosition.x + 1,
                                 currentPosition.y + direction};

    if(captureLeft.x >= 0)
        moves.push_back(captureLeft);
    if(captureRight.x < BoardConfig::GridSize)
        moves.push_back(captureRight);

    return moves;
}

bool Pawn::canCapture(sf::Vector2i currentPosition, sf::Vector2i toCapture)
{
    int dx = abs(toCapture.x - currentPosition.x);
    int dy = toCapture.y - currentPosition.y;

    if(dx == 1 && abs(dy) == 1)
        return true;

    return false;
}
