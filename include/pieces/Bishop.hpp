#pragma once

#include "../Piece.hpp"

class Bishop : public Piece
{
  private:
    static constexpr PieceKind kind = PieceKind::Bishop;

  public:
    Bishop(Side side, sf::Vector2i position)
        : Piece(kind, side, position)
    {}

    ~Bishop() = default;

    virtual std::vector<sf::Vector2i> getLegalMoves() const override;
};
