#include <SFML/Graphics.hpp>

enum class FontStyle
{
    Regular,
    Light,
    Medium,
    Semibold,
    Bold
};

namespace FontManager
{
    void loadFonts();
    const sf::Font &getFont(FontStyle style);
} // namespace FontManager
