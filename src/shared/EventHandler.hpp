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

class EventHandler
{
  protected:
    EventHandler() = default;

  public:
    virtual ~EventHandler() = default;

    virtual EventResult handleEvent(const EventContext &eventCtx)
    {
        return EventResult::Ignored;
    };
};
