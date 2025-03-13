#pragma once

#include "Board.hpp"
#include "Piece.hpp"
#include "UIManager.hpp"

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
  public:
    Game(sf::RenderWindow &window, UIManager uiManager, Board board)
        : window(window)
        , board(board)
    {}
    ~Game();

    void update();

  private:
    sf::RenderWindow &window;
    Board board;

    std::vector<std::unique_ptr<Piece>> whitePieces;
    std::vector<std::unique_ptr<Piece>> blackPieces;

    std::optional<std::reference_wrapper<Piece>> selectedPiece;
    Player currentPlayer;

    std::vector<std::unique_ptr<Move>> moves;
};
