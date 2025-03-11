#include "Window.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <optional>

Window::Window(uint width, uint height, const std::string &title)
    : width(width)
    , height(height)
    , title(title)
    , is_initialized(false)
{
    target.create(sf::VideoMode({width, height}), title);
    is_initialized = true;
}

Window::~Window()
{
    if(is_initialized)
    {
        target.close();
    }

    is_initialized = false;
}

sf::RenderWindow &Window::getRenderWindow()
{
    return target;
}

void Window::handleEvents()
{
    using Event = sf::Event;

    target.handleEvents([&](const Event::Closed &) { target.close(); },
                        [&](const Event::KeyPressed &keyPressEvent) {
                            handleKeyPress(keyPressEvent);
                        });
}

void Window::handleKeyPress(const std::optional<sf::Event::KeyPressed> &event)
{
    if(!event)
        return;

    switch(event->code)
    {
        case sf::Keyboard::Key::Escape:
            target.close();
            break;

        default:
            break;
    }
}
