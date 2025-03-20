#pragma once

#include "../Piece.hpp"

class Pawn : public Piece
{
  private:
    static constexpr PieceKind kind = PieceKind::Pawn;

  public:
    Pawn(Side side, sf::Vector2i position = SPRITE_INITIAL_POSITION)
        : Piece(kind, side, position)
    {}

    ~Pawn() = default;

    virtual std::vector<sf::Vector2i> getLegalMoves() const override;
};
