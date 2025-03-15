#pragma once

#include "../Piece.hpp"

class Bishop : public Piece
{
  private:
    static constexpr PieceType type = PieceType::Bishop;

  public:
    Bishop(sf::Vector2i position, Side side)
        : Piece(type, position, side)
    {}

    ~Bishop() = default;

    virtual std::vector<sf::Vector2i> getValidMoves() const override;
};
