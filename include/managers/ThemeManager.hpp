#pragma once

#include <SFML/Graphics/Color.hpp>
#include <string>

struct UITheme
{
    sf::Color background;
    sf::Color foreground;
    sf::Color foregroundDark;
    sf::Color accent;
    sf::Color highlight;
    sf::Color shadow;
};

struct BoardTheme
{
    sf::Color light;
    sf::Color dark;
    sf::Color hovered;
    sf::Color highlighted;
    sf::Color selected;
};

enum class ThemeID
{
    Default,
    Neon
};

struct Theme
{
    UITheme ui;
    BoardTheme board;
};

namespace ThemeManager
{
    void loadThemes();
    Theme loadTheme(const std::string &filename);
    Theme getTheme();
    void setTheme(ThemeID id);
    const sf::Color parseColor(const std::string &hex);
} // namespace ThemeManager
