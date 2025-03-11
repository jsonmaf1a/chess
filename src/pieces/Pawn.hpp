#pragma once

#include "../Piece.hpp"

#include <SFML/System.hpp>
#include <vector>

class Pawn : public Piece
{
  private:
    static constexpr const PieceType type = PieceType::Pawn;

  public:
    Pawn(sf::Vector2i position, PieceColor color)
        : Piece(type, position, color)
    {}

    ~Pawn() = default;

    virtual std::vector<sf::Vector2i> getValidMoves() const override;
};
