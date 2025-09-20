#pragma once

#include "Board.hpp"
#include "GameData.hpp"
#include "GameState.hpp"
#include "config/Layout.hpp"
#include <memory>
#include <wisp/core/managers/UIManager.hpp>
#include <wisp/events/EventHandler.hpp>

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

    void handleCastling(std::shared_ptr<Piece> piece, sf::Vector2i toPosition);
    std::optional<PieceKind> handleCapture(std::shared_ptr<Piece> piece,
                                           sf::Vector2i position);
    void handleIllegalMove();
    void handleNextTurn();
    void handleSelectPiece(std::shared_ptr<Piece> piece,
                           const sf::Vector2i cellPosition);

    void handleMovePiece(std::shared_ptr<Piece> piece, sf::Vector2i toPosition);

    bool isCheck();
    bool isCheckmate();
    bool isStalemate();
    bool isPromotion();
    bool isCastling(Piece &piece, sf::Vector2i toPosition);

    GameState &getState();

    void printInfo();

  private:
    sf::RenderWindow &window;
    UIManager &ui;
    std::shared_ptr<Board> board;
    GameState state;
    sf::Clock clock;
};
