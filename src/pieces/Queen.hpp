#pragma once

#include "../Piece.hpp"

class Queen : public Piece
{
  private:
    static constexpr PieceType type = PieceType::Queen;

  public:
    Queen(sf::Vector2i position, Side side)
        : Piece(type, position, side)
    {}

    ~Queen() = default;

    virtual std::vector<sf::Vector2i> getValidMoves() const override;
};
