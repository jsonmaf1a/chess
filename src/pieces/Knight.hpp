#pragma once

#include "../Piece.hpp"

#include <SFML/System.hpp>
#include <vector>

class Knight : public Piece
{
  private:
    static constexpr const PieceType type = PieceType::Knight;

  public:
    Knight(sf::Vector2i position, PieceColor color)
        : Piece(type, position, color)
    {}

    ~Knight() = default;

    virtual std::vector<sf::Vector2i> getValidMoves() const override;
};
