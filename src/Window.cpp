#include "Window.hpp"

#include <SFML/Window/Cursor.hpp>

void Window::update()
{
    window.clear(BACKGROUND);

    ui.draw(window);

    window.display();
}

void Window::handleKeyPress(const sf::Event::KeyPressed &event)
{
    switch(event.code)
    {
        case sf::Keyboard::Key::Escape:
            window.close();
            break;

        default:
            break;
    }
}

void Window::pollEvents()
{
    while(const std::optional event = window.pollEvent())
    {
        if(event->is<sf::Event::Closed>())
            window.close();

        if(auto keyPressedEvent = event->getIf<sf::Event::KeyPressed>())
            handleKeyPress(*keyPressedEvent);

        if(EventUtils::isMouseEvent(event.value()))
        {
            ui.handleEvent(EventContext{event.value(), window, cursorManager});
        }
    }
}

sf::RenderWindow &Window::getRenderWindow() { return window; }
