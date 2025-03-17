#pragma once

#include "CursorManager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

struct EventContext
{
    const sf::Event &event;
    sf::RenderWindow &window;
    CursorManager &cursorManager;
};
