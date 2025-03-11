#pragma once

#include "../Piece.hpp"

class Bishop : public Piece
{
  private:
    static constexpr const PieceType type = PieceType::Bishop;

  public:
    Bishop(sf::Vector2i position, PieceColor color)
        : Piece(type, position, color)
    {}

    ~Bishop() = default;

    virtual std::vector<sf::Vector2i> getValidMoves() const override;
};
