#pragma once

#include "../Piece.hpp"

class Knight : public Piece
{
  private:
    static constexpr PieceType type = PieceType::Knight;

  public:
    Knight(sf::Vector2i position, Side side)
        : Piece(type, position, side)
    {}

    ~Knight() = default;

    virtual std::vector<sf::Vector2i> getValidMoves() const override;
};
