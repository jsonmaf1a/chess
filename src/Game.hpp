#pragma once

#include "Board.hpp"
#include "Piece.hpp"

enum class Player
{
    White,
    Black
};

struct Move
{
  public:
    Player player;
    PieceType pieceType;
    sf::Vector2f position;
};

// TODO:
// * Count all moves to follow 50-move rule
// * Handle:
// * - mate
// * - stalemate (no possible moves, repetitions)
// * - win
// * - lose
class Game
{
  private:
    Board board;
    std::vector<std::unique_ptr<Piece>> whitePieces;
    std::vector<std::unique_ptr<Piece>> blackPieces;

    std::optional<std::reference_wrapper<Piece>> selectedPiece;
    Player currentPlayer;

    std::vector<std::unique_ptr<Move>> moves;

  public:
};
