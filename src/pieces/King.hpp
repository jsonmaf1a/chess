#pragma once

#include "../Piece.hpp"

class King : public Piece
{
  private:
    static constexpr PieceKind kind = PieceKind::King;

  public:
    King(Side side, sf::Vector2i position)
        : Piece(kind, side, position)
    {}

    ~King() = default;

    virtual std::vector<sf::Vector2i> getValidMoves(
        Board &boardState) const override;

  protected:
    virtual std::vector<sf::Vector2i> getLegalMoves() const override;
};
