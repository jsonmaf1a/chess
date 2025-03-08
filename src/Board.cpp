#include "Board.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

void Board::draw()
{
    for(int row = 0; row < gridSize; row++)
    {
        for(int col = 0; col < gridSize; col++)
        {
            sf::RectangleShape rect(sf::Vector2f(cellSize, cellSize));

            rect.setPosition(sf::Vector2f(col * cellSize, row * cellSize));

            sf::Color cellColor = getCellColor(row + col);
            rect.setFillColor(cellColor);

            target.draw(rect);
        }
    }
}

sf::Color Board::getCellColor(uint8_t position)
{
    return position % 2 == 0 ? colorLight : colorDark;
};
