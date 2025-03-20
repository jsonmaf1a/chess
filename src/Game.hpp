#pragma once

#include "Board.hpp"
#include "managers/UIManager.hpp"
#include "shared/EventHandler.hpp"
#include "shared/GameData.hpp"
#include "shared/Move.hpp"
#include "shared/config/Layout.hpp"

// TODO:
// * Count all moves to follow 50-move rule
// * Handle:
// * - mate (win/lose)
// * - stalemate (no possible moves, repetitions)
class Game : public EventHandler
{
  public:
    Game(sf::RenderWindow &window, UIManager &ui)
        : window(window)
        , ui(ui)
        , board(std::make_shared<Board>(window, LayoutConfig::BoardBounds,
                                        LayoutConfig::BoardViewport))
    {
        ui.addComponent(board);
    }
    ~Game() = default;

    virtual EventResult handleEvent(const EventContext &eventCtx) override;

    void start();
    void move(Piece &piece, sf::Vector2i newPosition);
    void nextTurn();
    bool isCheckmate();
    bool isStalemate();
    bool isPromotion();
    bool isCastling();
    void handlePieceSelection(const sf::Vector2i cellPosition,
                              const std::shared_ptr<Piece> maybePiece);

    void printGameState();

  private:
    sf::RenderWindow &window;
    UIManager &ui;
    std::shared_ptr<Board> board;
    std::vector<std::unique_ptr<Move>> moves;
    std::optional<std::reference_wrapper<Piece>> selectedPiece;

    Side currentSide = Side::White;
    bool isStarted = false;
};
