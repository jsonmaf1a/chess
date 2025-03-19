#pragma once

#include "../Piece.hpp"

class Rook : public Piece
{
  private:
    static constexpr PieceKind kind = PieceKind::Rook;

  public:
    Rook(sf::Vector2i position, Side side)
        : Piece(kind, position, side)
    {}

    ~Rook() = default;

    virtual std::vector<sf::Vector2i> getLegalMoves(
        std::vector<std::shared_ptr<Piece>> onBoard) const override;
};
