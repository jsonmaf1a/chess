#pragma once

#include "../Piece.hpp"

class Queen : public Piece
{
  private:
    static constexpr const PieceType type = PieceType::Queen;

  public:
    Queen(sf::Vector2i position, PieceColor color)
        : Piece(type, position, color)
    {}

    ~Queen() = default;

    virtual std::vector<sf::Vector2i> getValidMoves() const override;
};
