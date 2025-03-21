#pragma once

#include "Board.hpp"
#include "GameState.hpp"
#include "managers/UIManager.hpp"
#include "shared/EventHandler.hpp"
#include "shared/config/Layout.hpp"
#include <memory>

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

    void update();
    void move(Piece &piece, sf::Vector2i newPosition);
    void handleIllegalMove();
    bool isCheck();
    bool isCheckmate();
    bool isStalemate();
    bool isPromotion();
    bool isCastling();
    void handlePieceSelection(const sf::Vector2i cellPosition,
                              const std::shared_ptr<Piece> maybePiece);

    GameState &getState();

  private:
    sf::RenderWindow &window;
    UIManager &ui;
    std::shared_ptr<Board> board;
    GameState state = {50, Side::White, false,
                       GameModePresets::createCustomPreset({10 * 1000})};
    sf::Clock clock;
};
