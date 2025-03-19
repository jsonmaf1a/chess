#pragma once

#include "../Piece.hpp"

class Bishop : public Piece
{
  private:
    static constexpr PieceKind kind = PieceKind::Bishop;

  public:
    Bishop(sf::Vector2i position, Side side)
        : Piece(kind, position, side)
    {}

    ~Bishop() = default;

    virtual std::vector<sf::Vector2i> getLegalMoves(
        std::vector<std::shared_ptr<Piece>> onBoard) const override;
};
