#pragma once

#include "../Piece.hpp"

class Rook : public Piece
{
  private:
    static constexpr PieceKind kind = PieceKind::Rook;

  public:
    Rook(Side side, sf::Vector2i position = SPRITE_INITIAL_POSITION)
        : Piece(kind, side, position)
    {}

    ~Rook() = default;

    virtual std::vector<sf::Vector2i> getLegalMoves() const override;
};
