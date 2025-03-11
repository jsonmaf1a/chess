#pragma once

#include "../Piece.hpp"

class Rook : public Piece
{
  private:
    static constexpr const PieceType type = PieceType::Rook;

  public:
    Rook(sf::Vector2i position, PieceColor color)
        : Piece(type, position, color)
    {}

    ~Rook() = default;

    virtual std::vector<sf::Vector2i> getValidMoves() const override;
};
