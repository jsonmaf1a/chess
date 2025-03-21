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

    void handlePieceMove(Piece &piece, sf::Vector2i toPosition);
    void handleCastling(Piece &piece, sf::Vector2i toPosition);
    std::optional<PieceKind> handleCapturing(Piece &piece,
                                             sf::Vector2i position);
    void handleIllegalMove();
    void handleNextTurn();
    void handlePieceSelection(const sf::Vector2i cellPosition,
                              const std::shared_ptr<Piece> maybePiece);

    void movePiece(Piece &piece, sf::Vector2i toPosition);

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
    GameState state = {50, Side::White, false, GameModePresets::Rapid10};
    sf::Clock clock;
};
