#pragma once

#include "UIManager.hpp"
#include "shared/CursorManager.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Cursor.hpp>
#include <string>

class Window
{
  public:
    static constexpr const sf::Color BACKGROUND = {30, 30, 30, 255};

    static constexpr const uint WINDOW_WIDTH = 1200;
    static constexpr const uint WINDOW_HEIGHT = 800;
    static constexpr const char *WINDOW_TITLE = "sfml-chess";

    Window(uint width = WINDOW_WIDTH, uint height = WINDOW_HEIGHT,
           const std::string &title = WINDOW_TITLE);
    ~Window();

    void update();
    void pollEvents();
    void createRootComponents();

    bool isOpen() { return window.isOpen(); }

  private:
    sf::RenderWindow window;
    UIManager uiManager;
    CursorManager cursorManager;

    const uint width;
    const uint height;
    const std::string title;

    bool is_initialized = false;

    void handleKeyPress(const sf::Event::KeyPressed &event);
};
