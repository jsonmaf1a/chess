#pragma once

#include "../Piece.hpp"

class Knight : public Piece
{
  private:
    static constexpr PieceKind kind = PieceKind::Knight;

  public:
    Knight(Side side, sf::Vector2i position = SPRITE_INITIAL_POSITION)
        : Piece(kind, side, position)
    {}

    ~Knight() = default;

    virtual std::vector<sf::Vector2i> getLegalMoves(
        std::vector<std::shared_ptr<Piece>> onBoard) const override;
};
