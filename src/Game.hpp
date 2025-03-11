#pragma once

#include "Board.hpp"
#include "Piece.hpp"
#include <SFML/System/Vector2.hpp>

#include <memory>
#include <optional>
#include <vector>

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
