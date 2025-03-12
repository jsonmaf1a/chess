#pragma once

#include "Piece.hpp"
#include "utils/UIComponent.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

// TODO:
class Board : public UIComponent
{
  public:
    static constexpr const int GRID_SIZE = 8;
    static constexpr const int CELL_SIZE = 100;

    Board(sf::FloatRect bounds, sf::RenderWindow &target);
    ~Board() = default;

    void createPieces();
    void initializePieces();

    virtual void drawSelf(sf::RenderWindow &window) override;
    virtual EventResult handleSelfEvent(const sf::Event &event) override;

    std::string toChessNotation(const sf::Vector2i &pos) const;
    sf::Vector2i fromChessNotation(const std::string &notation) const;

    sf::Vector2f mapToViewCoords(sf::RenderWindow &renderWindow,
                                 sf::Vector2i mousePos);

    sf::View boardView;

  private:
    const sf::Color colorCellDark = {119, 163, 169, 255};
    const sf::Color colorCellLight = {220, 220, 220, 255};

    std::vector<std::shared_ptr<Piece>> pieces;

    sf::Color getCellColor(int position) const;
};
