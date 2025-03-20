#pragma once

#include "managers/CursorManager.hpp"
#include "managers/EventDispatcher.hpp"
#include "managers/UIManager.hpp"
#include "shared/config/Layout.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Cursor.hpp>
#include <string>

class Window
{
  public:
    static constexpr sf::Color BACKGROUND = {30, 30, 30, 255};
    static constexpr const char *WINDOW_TITLE = "sfml-chess";

    Window(uint width = LayoutConfig::WindowBounds.x,
           uint height = LayoutConfig::WindowBounds.y,
           const std::string &title = WINDOW_TITLE);
    ~Window();

    void update();
    void pollEvents();
    bool isOpen() const;

    sf::RenderWindow &getRenderWindow();
    EventDispatcher &getEventDispatcher();
    UIManager &getUI();

  private:
    sf::RenderWindow window;
    EventDispatcher dispatcher;
    CursorManager cursorManager;
    UIManager ui;

    bool isInitialized = false;
};
