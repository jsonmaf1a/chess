#include "Board.hpp"
#include "Window.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

int main()
{
    Window window(1000, 800, "sfml-chess");

    sf::View boardView(sf::FloatRect({0, 0}, sf::Vector2f(800, 800)));
    boardView.setViewport(sf::FloatRect({0.2f, 0.f}, {0.8f, 1.f}));

    sf::View uiView(sf::FloatRect({0, 0}, {200, 800}));
    uiView.setViewport(sf::FloatRect({0.f, 0.f}, {0.2f, 1.f}));

    sf::RectangleShape uiViewBg;
    uiViewBg.setSize(sf::Vector2f(200, 800));
    uiViewBg.setPosition({0, 0});
    uiViewBg.setFillColor(Window::BACKGROUND);

    auto &target = window.getRenderWindow();
    target.setVerticalSyncEnabled(true);

    Board board(target);

    while(target.isOpen())
    {
        window.handleEvents();
        target.clear(Window::BACKGROUND);

        target.setView(uiView);
        target.draw(uiViewBg);

        target.setView(boardView);
        board.draw();

        target.display();
    }

    return 0;
}
