#include "Notation.hpp"
#include <stdexcept>

std::string Notation::toChessNotation(const sf::Vector2i &position)
{
    char file = 'A' + position.x;
    char rank = '1' + (7 - position.y);

    return std::string(1, file) + rank;
}

sf::Vector2i Notation::fromChessNotation(const std::string &notation)
{
    if(notation.length() != 2)
        throw std::invalid_argument("Invalid notation");

    int x = notation[0] - 'A';
    int y = 7 - (notation[1] - '1');

    return {x, y};
}
