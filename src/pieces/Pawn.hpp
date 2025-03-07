#pragma once

#include "../Piece.hpp"

class Pawn : public Piece
{
  void moveTo(sf::Vector2i newPosition) override;
  virtual std::vector<sf::Vector2i> getValidMoves() const override;
};
