#pragma once

#include "UIManager.hpp"
#include "config/Layout.hpp"
#include "shared/CursorManager.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Cursor.hpp>
#include <string>

class Window
{
  public:
    static constexpr sf::Color BACKGROUND = {30, 30, 30, 255};
    static constexpr const char *WINDOW_TITLE = "sfml-chess";

    Window(uint width = Layout::WindowBounds.x,
           uint height = Layout::WindowBounds.y,
           const std::string &title = WINDOW_TITLE);
    ~Window();

    void update();
    void pollEvents();
    sf::RenderWindow &getRenderWindow();
    EventDispatcher &getEventDispatcher();
    UIManager &getUI();

    bool isOpen() const;

  private:
    sf::RenderWindow window;
    EventDispatcher dispatcher;
    CursorManager cursorManager;
    UIManager ui;

    bool isInitialized = false;

    void handleKeyPress(const sf::Event::KeyPressed &event);
};
