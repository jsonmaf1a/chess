#include "Window.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <optional>

sf::RenderWindow &Window::getRenderWindow()
{
    return rw;
}

void Window::handleEvents()
{
    // while(const std::optional event = rw.pollEvent())
    //     {
    //         if(event->is<sf::Event::Closed>()
    //            || isKeyPressed(event, sf::Keyboard::Key::Escape))
    //             {
    //                 rw.close();
    //             }
    //     }

    rw.handleEvents([&](const sf::Event::Closed &) { rw.close(); },
                    [&](const sf::Event::KeyPressed &keyPressEvent) {
                        handleKeyPress(keyPressEvent);
                    });
}

void Window::handleKeyPress(const std::optional<sf::Event::KeyPressed> &event)
{
    if(!event.has_value())
        return;

    switch(event->code)
    {

        case sf::Keyboard::Key::Escape:
            rw.close();

        default:
            break;
    }
}
