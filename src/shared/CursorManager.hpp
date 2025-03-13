#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class CursorManager
{
  public:
    CursorManager(sf::RenderWindow &window)
        : window(window)
    {
        handCursor = std::make_unique<sf::Cursor>(
            *sf::Cursor::createFromSystem(sf::Cursor::Type::Hand));

        defaultCursor = std::make_unique<sf::Cursor>(
            *sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow));
    }

    void setHandCursor() { window.setMouseCursor(*handCursor); }
    void resetCursor() { window.setMouseCursor(*defaultCursor); }

  private:
    sf::RenderWindow &window;
    std::unique_ptr<sf::Cursor> handCursor;
    std::unique_ptr<sf::Cursor> defaultCursor;
};
