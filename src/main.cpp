#include "Board.hpp"
#include "Window.hpp"

#include <SFML/Graphics.hpp>

int main()
{
    Window window(800, 800, "sfml-chess");

    auto &rw = window.getRenderWindow();

    Board board(rw);

    while(rw.isOpen())
    {
        window.handleEvents();

        rw.clear();
        board.draw();

        rw.display();
    }

    return 0;
}
