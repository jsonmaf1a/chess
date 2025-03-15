#include "Notation.hpp"
#include <stdexcept>

Notation Notation::toChessNotation(const sf::Vector2i &position)
{
    char file = 'A' + position.x;
    char rank = '1' + position.y;

    return Notation(file, rank);
}

sf::Vector2i Notation::fromChessNotation(const Notation &notation)
{
    int x = notation.file - 'A';
    int y = 7 - (notation.rank - '1');

    return {x, y};
}

sf::Vector2i Notation::fromChessNotation(const std::string &notation)
{
    if(notation.length() != 2)
        throw std::invalid_argument("Invalid notation");

    int x = notation[0] - 'A';
    int y = 7 - (notation[1] - '1');

    return {x, y};
}
