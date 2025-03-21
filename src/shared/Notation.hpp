#pragma once

#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <string>

struct Notation
{
  public:
    char file;
    char rank;

    template <typename T>
        requires std::is_arithmetic_v<T>
    static Notation toChessNotation(const sf::Vector2<T> position)
    {
        char file = 'A' + position.x;
        char rank = '8' - position.y;

        return Notation(file, rank);
    }

    static sf::Vector2i fromChessNotation(const Notation &notation);
    static sf::Vector2i fromChessNotation(const std::string &notation);

    friend std::ostream &operator<<(std::ostream &os, const Notation &notation)
    {
        os << "[" << notation.file << notation.rank << "]";
        return os;
    }
};
