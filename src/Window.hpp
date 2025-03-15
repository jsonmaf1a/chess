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

    Window(UIManager &ui, uint width = Layout::WindowBounds.x,
           uint height = Layout::WindowBounds.y,
           const std::string &title = WINDOW_TITLE)
        : width(width)
        , height(height)
        , title(title)
        , ui(ui)
        , cursorManager(window)
    {
        window.create(sf::VideoMode({width, height}), title, sf::Style::None,
                      sf::State::Windowed);
        window.setVerticalSyncEnabled(true);

        ui.addComponent(std::make_shared<Sidebar>(window, Layout::SidebarBounds,
                                                  Layout::SidebarViewport));

        isInitialized = true;
    }

    ~Window()
    {
        if(isInitialized)
            window.close();

        isInitialized = false;
    }

    void update();
    void pollEvents();
    sf::RenderWindow &getRenderWindow();

    bool isOpen() { return window.isOpen(); }

  private:
    sf::RenderWindow window;
    UIManager &ui;
    CursorManager cursorManager;

    const uint width;
    const uint height;
    const std::string title;

    bool isInitialized = false;

    void handleKeyPress(const sf::Event::KeyPressed &event);
};
