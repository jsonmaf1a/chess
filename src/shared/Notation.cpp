#include "Notation.hpp"
#include <stdexcept>

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
