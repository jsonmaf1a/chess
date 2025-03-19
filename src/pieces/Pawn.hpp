#pragma once

#include "../Piece.hpp"

class Pawn : public Piece
{
  private:
    static constexpr PieceKind kind = PieceKind::Pawn;

  public:
    Pawn(sf::Vector2i position, Side side)
        : Piece(kind, position, side)
    {}

    ~Pawn() = default;

    virtual std::vector<sf::Vector2i> getLegalMoves(
        std::vector<std::shared_ptr<Piece>> onBoard) const override;
};
