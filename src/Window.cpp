#include "Window.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

sf::RenderWindow &Window::getRenderWindow()
{
    return rw;
}

void Window::pollEvents()
{
    while (const std::optional event = rw.pollEvent())
    {
        if (event->is<sf::Event::Closed>() ||
            (event->is<sf::Event::KeyPressed>() &&
             event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape))
        {
            rw.close();
        }
    }
}
