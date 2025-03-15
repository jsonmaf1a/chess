#pragma once

#include "../Piece.hpp"

class King : public Piece
{
  private:
    static constexpr PieceType type = PieceType::King;

  public:
    King(sf::Vector2i position, Side side)
        : Piece(type, position, side)
    {}

    ~King() = default;

    virtual std::vector<sf::Vector2i> getValidMoves() const override;
};
