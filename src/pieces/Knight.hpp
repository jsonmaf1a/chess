#pragma once

#include "../Piece.hpp"

class Knight : public Piece
{
  private:
    static constexpr PieceKind kind = PieceKind::Knight;

  public:
    Knight(sf::Vector2i position, Side side)
        : Piece(kind, position, side)
    {}

    ~Knight() = default;

    virtual std::vector<sf::Vector2i> getLegalMoves() const override;
};
