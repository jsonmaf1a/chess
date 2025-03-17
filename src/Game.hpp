#pragma once

#include "Board.hpp"
#include "UIManager.hpp"
#include "shared/EventHandler.hpp"
#include "shared/Move.hpp"
#include "shared/Side.hpp"
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
        , board(std::make_shared<Board>(window, Layout::BoardBounds,
                                        Layout::BoardViewport))
    {
        ui.addComponent(board);
    }
    ~Game() = default;

    void start();
    void move(Piece &piece, sf::Vector2i newPosition);
    void nextTurn();
    bool isCheckmate();
    bool isStalemate();
    bool isPawnPromotion();

    virtual EventResult handleEvent(const EventContext &eventCtx) override;

  private:
    sf::RenderWindow &window;
    std::shared_ptr<Board> board;
    std::vector<std::unique_ptr<Move>> moves;
    std::optional<std::reference_wrapper<Piece>> selectedPiece;

    Side currentSide = Side::White;
};
