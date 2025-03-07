#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cstdint>

class Board
{
  public:
    Board(sf::RenderWindow &target) : gridSize(8), cellSize(100), target(target)
    {
    }

    ~Board() {};

    void draw();

  private:
    sf::RenderWindow &target;

    const uint8_t gridSize;
    const uint8_t cellSize;

    const sf::Color colorDark = {119, 163, 169, 255};
    const sf::Color colorLight = {220, 220, 220, 255};

    sf::Color getCellColor(uint8_t position);
};
