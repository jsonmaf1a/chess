#include "Window.hpp"

Window::Window(uint width, uint height, const std::string &title)
    : width(width)
    , height(height)
    , title(title)
    , is_initialized(false)
{
    renderWindow.create(sf::VideoMode({width, height}), title);
    is_initialized = true;
}

Window::~Window()
{
    if(is_initialized)
    {
        renderWindow.close();
    }

    is_initialized = false;
}

sf::RenderWindow &Window::getRenderWindow()
{
    return renderWindow;
}

// void Window::handleEvents()
// {
// }

void Window::handleKeyPress(const sf::Event::KeyPressed &event)
{
    switch(event.code)
    {
        case sf::Keyboard::Key::Escape:
            renderWindow.close();
            break;

        default:
            break;
    }
}
