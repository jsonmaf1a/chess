#pragma once

#include "../Piece.hpp"

class Queen : public Piece
{
  private:
    static constexpr PieceKind kind = PieceKind::Queen;

  public:
    Queen(sf::Vector2i position, Side side)
        : Piece(kind, position, side)
    {}

    ~Queen() = default;

    virtual std::vector<sf::Vector2i> getLegalMoves(
        std::vector<std::shared_ptr<Piece>> onBoard) const override;
};
