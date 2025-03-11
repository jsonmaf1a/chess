#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

class Window
{
  public:
    static constexpr const sf::Color BACKGROUND = {30, 30, 30, 255};

    Window(uint width, uint height, const std::string &title);
    ~Window();

    sf::RenderWindow &getRenderWindow();

    void handleEvents();
    void handleKeyPress(const std::optional<sf::Event::KeyPressed> &event);

  private:
    sf::RenderWindow target;

    const uint width;
    const uint height;
    const std::string title;

    bool is_initialized;
};
