#pragma once

#include "../Piece.hpp"

class Queen : public Piece
{
  private:
    static constexpr PieceKind kind = PieceKind::Queen;

  public:
    Queen(Side side, sf::Vector2i position = SPRITE_INITIAL_POSITION)
        : Piece(kind, side, position)
    {}

    ~Queen() = default;

    virtual std::vector<sf::Vector2i> getLegalMoves(
        std::vector<std::shared_ptr<Piece>> onBoard) const override;
};
