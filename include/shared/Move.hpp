#pragma once

#include "../Piece.hpp"
#include <SFML/System/Vector2.hpp>

struct Move
{
  public:
    Piece &piece;
    sf::Vector2i from;
    sf::Vector2i to;
    std::optional<PieceKind> captured;
};
