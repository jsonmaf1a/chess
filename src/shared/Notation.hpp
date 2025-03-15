#pragma once

#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <string>

struct Notation
{
  public:
    char file;
    char rank;

    Notation(char file, char rank)
        : file(file)
        , rank(rank)
    {}

    static Notation toChessNotation(const sf::Vector2i &pos);
    static sf::Vector2i fromChessNotation(const Notation &notation);
    static sf::Vector2i fromChessNotation(const std::string &notation);

    friend std::ostream &operator<<(std::ostream &os, const Notation &notation)
    {
        os << "[" << notation.file << notation.rank << "]";
        return os;
    }
};
