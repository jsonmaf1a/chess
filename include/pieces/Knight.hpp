#pragma once

#include "../Piece.hpp"

class Knight : public Piece
{
  private:
    static constexpr PieceKind kind = PieceKind::Knight;

  public:
    Knight(Side side, sf::Vector2i position)
        : Piece(kind, side, position)
    {}

    ~Knight() = default;

    virtual std::vector<sf::Vector2i> getLegalMoves() const override;
};
