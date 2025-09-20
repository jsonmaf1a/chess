#pragma once

#include "../Piece.hpp"

class Queen : public Piece
{
  private:
    static constexpr PieceKind kind = PieceKind::Queen;

  public:
    Queen(Side side, sf::Vector2i position)
        : Piece(kind, side, position)
    {}

    ~Queen() = default;

    virtual std::vector<sf::Vector2i> getValidMoves(
        Board &boardState) const override;

  protected:
    virtual std::vector<sf::Vector2i> getLegalMoves() const override;
};
