#pragma once

#include "../Piece.hpp"

class Pawn : public Piece
{
  private:
    static constexpr PieceKind kind = PieceKind::Pawn;

  public:
    Pawn(Side side, sf::Vector2i position)
        : Piece(kind, side, position)
    {}

    ~Pawn() = default;
    static bool canCapture(sf::Vector2i currentPosition,
                           sf::Vector2i toCapture);
    virtual std::vector<sf::Vector2i> getValidMoves(
        Board &boardState) const override;

  protected:
    virtual std::vector<sf::Vector2i> getLegalMoves() const override;
};
