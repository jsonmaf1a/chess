#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <string>

class Window
{
  public:
    static constexpr sf::Color background = {30, 30, 30, 255};

    Window(uint width, uint height, const std::string &title)
        : width(width), height(height), title(title), is_initialized(false)
    {
        rw.create(sf::VideoMode({width, height}), title.c_str());
        is_initialized = true;
    }

    ~Window()
    {
        if(is_initialized)
        {
            rw.close();
        }

        is_initialized = false;
    }

    sf::RenderWindow &getRenderWindow();
    void handleEvents();
    void handleKeyPress(const std::optional<sf::Event::KeyPressed> &event);

  private:
    sf::RenderWindow rw;

    const uint width;
    const uint height;
    const std::string title;

    bool is_initialized;
};
