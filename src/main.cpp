#include "Board.hpp"
#include "UIManager.hpp"
#include "Window.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

int main()
{
    Window mainWindow(1100, 800, "sfml-chess");
    UIManager uiManager;

    sf::FloatRect panelBounds({0, 0}, sf::Vector2f(300, 800));
    sf::View panelView(panelBounds);
    panelView.setViewport(sf::FloatRect({0.f, 0.f}, {0.3f, 1.f}));

    sf::RectangleShape panelViewBg;
    panelViewBg.setSize(sf::Vector2f(300, 800));
    panelViewBg.setPosition({0, 0});
    panelViewBg.setFillColor(Window::BACKGROUND);

    auto &renderWindow = mainWindow.getRenderWindow();
    renderWindow.setVerticalSyncEnabled(true);

    // auto uiPanel = std::make_shared<Panel>(panelBounds, "UI Panel",
    //                                        sf::Color(50, 50, 50, 200));

    sf::FloatRect boardBounds({0, 0}, sf::Vector2f(800, 800));
    // Board board(boardBounds, renderWindow);

    auto board = std::make_shared<Board>(boardBounds, renderWindow);

    uiManager.addComponent(board);

    while(renderWindow.isOpen())
    {
        while(const std::optional event = renderWindow.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
                renderWindow.close();

            if(auto keyPressedEvent = event->getIf<sf::Event::KeyPressed>())
            {
                mainWindow.handleKeyPress(*keyPressedEvent);
                // ...
            }

            // NOTE: do same with:
            // * sf::Event::MouseButtonPressed
            // * sf::Event::MouseButtonReleased
            if(auto mouseEvent = event->getIf<sf::Event::MouseMoved>())
            {
                const float PANEL_WIDTH_RATIO = 0.3f;

                sf::Vector2i mousePos = sf::Mouse::getPosition(renderWindow);

                sf::Vector2f worldPosPanel =
                    renderWindow.mapPixelToCoords(mousePos, panelView);
                sf::Vector2f worldPosBoard =
                    board->mapToViewCoords(renderWindow, mousePos);

                const auto &worldPos =
                    (mousePos.x < renderWindow.getSize().x * PANEL_WIDTH_RATIO)
                        ? worldPosPanel
                        : worldPosBoard;

                auto transformedEvent = *mouseEvent;

                transformedEvent.position.x = worldPos.x;
                transformedEvent.position.y = worldPos.y;

                uiManager.handleEvent(transformedEvent);
            }
        }

        renderWindow.clear(Window::BACKGROUND);

        renderWindow.setView(panelView);
        renderWindow.draw(panelViewBg);

        renderWindow.setView(board->boardView);
        uiManager.draw(renderWindow);

        renderWindow.display();
    }

    return 0;
}
