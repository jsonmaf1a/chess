#pragma once

#include "Board.hpp"
#include "UIManager.hpp"
#include "config/Layout.hpp"
#include "shared/EventHandler.hpp"
#include "shared/GameData.hpp"

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

    void run();
    void makeMove();
    bool isMate();
    bool isStalemate();
    bool isPawnPromotion();

    virtual EventResult handleEvent(const EventContext &eventCtx) override;

  private:
    sf::RenderWindow &window;
    std::shared_ptr<Board> board;
    Side currentSide = Side::White;
    std::vector<std::unique_ptr<Move>> moves;
    std::optional<std::reference_wrapper<Piece>> selectedPiece;
};
