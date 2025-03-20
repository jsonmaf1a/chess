#pragma once

#include "Piece.hpp"
#include "shared/Move.hpp"
#include "shared/UIComponent.hpp"
#include "shared/config/Board.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Board : public UIComponent
{
  public:
    Board(sf::RenderWindow &target, sf::FloatRect bounds,
          sf::FloatRect viewport)
        : UIComponent(bounds)
    {
        setView(bounds);
        view->setViewport(viewport);

        initializePieces();
    }
    ~Board() = default;

    virtual void drawSelf(sf::RenderWindow &window) override;
    void drawPossibleMove(sf::RenderWindow &window,
                          const sf::Vector2i position);
    void drawHighlights(sf::RenderWindow &window);
    void drawCell(sf::RenderWindow &window, sf::Vector2i position,
                  sf::Color color = sf::Color::Transparent);

    sf::Vector2i getCellFromMousePos(const sf::Vector2i mousePos,
                                     const sf::RenderWindow &window,
                                     const sf::View &view) const;

    virtual EventResult handleSelfEvent(const EventContext &eventCtx) override;

    void initializePieces();
    void createPieces();
    void updatePiecePosition(Piece &piece, sf::Vector2i newPosition);
    std::shared_ptr<Piece> getPiece(sf::Vector2i cellPosition) const;
    std::vector<std::shared_ptr<Piece>> getPiecesOnBoard();

    void setSelectedCell(const sf::Vector2i cellPosition);
    void setHoveredCell(const sf::Vector2i cellPosition);
    void setLastMoveCells(const Move move);
    void setPossibleMoves(const std::vector<sf::Vector2i> possibleMoves);

    void resetSelectedCell();
    void resetHoveredCell();
    void resetLastMoveCells();
    void resetPossibleMoves();

    const sf::View &getView() const;
    void printSelf() const;

  private:
    std::shared_ptr<Piece> _board[BoardConfig::GridSize]
                                 [BoardConfig::GridSize] = {nullptr};

    std::optional<std::pair<sf::Vector2i, sf::Vector2i>> lastMoveCells =
        std::nullopt;
    std::optional<sf::Vector2i> hoveredCell = std::nullopt;
    std::optional<sf::Vector2i> selectedCell = std::nullopt;
    std::vector<sf::Vector2i> possibleMoves;

    // TODO: intoduce theme manager and use it to get colors and shit
    static constexpr sf::Color colorDark = {119, 148, 85, 255};
    static constexpr sf::Color colorLight = {235, 235, 208, 255};

    void drawLabels(sf::RenderWindow &window);
    sf::Color getCellColor(int position) const;
    bool isMouseOverCell(sf::Vector2i mousePos);

    template <typename T>
        requires std::is_base_of<Piece, T>::value
    void placePiece(const std::string &pos, Side side);
};
