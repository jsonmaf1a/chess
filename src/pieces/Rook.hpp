#pragma once

#include "../Piece.hpp"

class Rook : public Piece
{
  private:
    static constexpr PieceType type = PieceType::Rook;

  public:
    Rook(sf::Vector2i position, Side side)
        : Piece(type, position, side)
    {}

    ~Rook() = default;

    virtual std::vector<sf::Vector2i> getValidMoves() const override;
};
