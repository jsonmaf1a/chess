#pragma once

#include "../Piece.hpp"

class King : public Piece
{
  private:
    static constexpr PieceKind kind = PieceKind::King;

  public:
    King(sf::Vector2i position, Side side)
        : Piece(kind, position, side)
    {}

    ~King() = default;

    virtual std::vector<sf::Vector2i> getLegalMoves() const override;
};
