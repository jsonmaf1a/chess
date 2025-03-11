#pragma once

#include "Piece.hpp"

class Board
{
  public:
    static constexpr const int GRID_SIZE = 8;
    static constexpr const int CELL_SIZE = 100;

    Board(sf::RenderTarget &target);
    ~Board() = default;

    void draw();
    void initializePieces();

  private:
    sf::RenderTarget &target;

    const sf::Color colorDark = {119, 163, 169, 255};
    const sf::Color colorLight = {220, 220, 220, 255};

    std::vector<std::shared_ptr<Piece>> pieces;

    sf::Color getCellColor(int position);
};
