#pragma once

#include "CursorManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

enum class EventResult
{
    Ignored,
    Handled, //  NOTE: event was handled, but can continue propagation
    Consumed //  NOTE: event was handled and should stop propagation
};

struct EventContext
{
    const sf::Event &event;
    sf::RenderWindow &window;
    CursorManager &cursorManager;
};

namespace EventUtils
{
    inline bool isMouseEvent(const sf::Event &event)
    {
        return event.is<sf::Event::MouseMoved>() ||
               event.is<sf::Event::MouseButtonPressed>() ||
               event.is<sf::Event::MouseButtonReleased>();
    }
} // namespace EventUtils
