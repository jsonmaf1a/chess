#pragma once

#include "../Piece.hpp"

class Rook : public Piece
{
  private:
    static constexpr PieceKind kind = PieceKind::Rook;

  public:
    Rook(Side side, sf::Vector2i position)
        : Piece(kind, side, position)
    {}

    ~Rook() = default;

    virtual std::vector<sf::Vector2i> getValidMoves(
        Board &boardState) const override;

    virtual std::vector<sf::Vector2i> getLegalMoves() const override;
};
