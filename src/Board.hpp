#pragma once

#include "Piece.hpp"
#include "shared/UIComponent.hpp"

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

    static constexpr int GRID_SIZE = 8;
    static constexpr float CELL_SIZE = 100.f;

    std::vector<std::shared_ptr<Piece>> pieces;
    std::shared_ptr<Piece> board[GRID_SIZE][GRID_SIZE] = {nullptr};

    virtual void drawSelf(sf::RenderWindow &window) override;
    virtual EventResult handleSelfEvent(const EventContext &eventCtx) override;
    void initializePieces();
    void createPieces();
    const sf::View &getView() const;
    std::shared_ptr<Piece> getPiece(sf::Vector2i cellPosition) const;
    sf::Vector2i getCellFromMousePos(const sf::Vector2i &mousePos,
                                     const sf::RenderWindow &window,
                                     const sf::View &view) const;

  private:
    sf::Vector2i hoveredCell = {-1, -1};

    // TODO: intoduce theme manager and use it to get colors and shit
    static constexpr sf::Color colorDark = {119, 163, 169, 255};
    static constexpr sf::Color colorLight = {220, 220, 220, 255};

    void drawLabels(sf::RenderWindow &window);
    sf::Color getCellColor(int position) const;
    bool isMouseOverCell(sf::Vector2i mousePos);
    void resetHoveredCell();
};
