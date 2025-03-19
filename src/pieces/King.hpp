#pragma once

#include "../Piece.hpp"

class King : public Piece
{
  private:
    static constexpr PieceKind kind = PieceKind::King;

  public:
    King(Side side, sf::Vector2i position = SPRITE_INITIAL_POSITION)
        : Piece(kind, side, position)
    {}

    ~King() = default;

    virtual std::vector<sf::Vector2i> getLegalMoves(
        std::vector<std::shared_ptr<Piece>> onBoard) const override;
};
