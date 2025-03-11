#pragma once

#include "../Piece.hpp"

#include <SFML/System.hpp>
#include <vector>

class King : public Piece
{
  private:
    static constexpr const PieceType type = PieceType::King;

  public:
    King(sf::Vector2i position, PieceColor color)
        : Piece(type, position, color)
    {}

    ~King() = default;

    virtual std::vector<sf::Vector2i> getValidMoves() const override;
};
