#pragma once

#include <SFML/Window/Event.hpp>

namespace EventUtils
{
    static bool isMouseEvent(const sf::Event &event)
    {
        return event.is<sf::Event::MouseMoved>() ||
               event.is<sf::Event::MouseButtonPressed>() ||
               event.is<sf::Event::MouseButtonReleased>();
    }

    static bool isLeftClickEvent(const sf::Event &event)
    {
        auto mouseClickEvent = event.getIf<sf::Event::MouseButtonPressed>();
        return mouseClickEvent &&
               mouseClickEvent->button == sf::Mouse::Button::Left;
    }
} // namespace EventUtils
