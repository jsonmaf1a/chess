#pragma once

#include "../Piece.hpp"

class Pawn : public Piece
{
  private:
    static constexpr PieceType type = PieceType::Pawn;

  public:
    Pawn(sf::Vector2i position, Side side)
        : Piece(type, position, side)
    {}

    ~Pawn() = default;

    virtual std::vector<sf::Vector2i> getValidMoves() const override;
};
