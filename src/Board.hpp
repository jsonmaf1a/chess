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
          sf::FloatRect viewport);
    ~Board() = default;

    static constexpr const int GRID_SIZE = 8;
    static constexpr const float CELL_SIZE = 100.f;

    void createPieces();
    void initializePieces();

    virtual void drawSelf(sf::RenderWindow &window) override;
    virtual EventResult handleSelfEvent(const EventContext &eventCtx) override;

  private:
    std::vector<std::shared_ptr<Piece>> pieces;

    int hoveredRow = -1;
    int hoveredCol = -1;

    // TODO: intoduce theme manager and use it to get colors and shit
    static constexpr const sf::Color colorDark = {119, 163, 169, 255};
    static constexpr const sf::Color colorLight = {220, 220, 220, 255};

    void drawLabels(sf::RenderWindow &window);
    sf::Vector2f getNormalizedMousePosition(const sf::Vector2i &mousePos,
                                            const sf::RenderWindow &window);
    sf::Color getCellColor(int position) const;
    bool isMouseOverCell(sf::Vector2i mousePos);
    void setHoveredCell(sf::Vector2i position);
    void resetHoveredCell();
};
