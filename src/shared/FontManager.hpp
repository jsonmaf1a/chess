#include <SFML/Graphics.hpp>
#include <unordered_map>

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
    static std::unordered_map<FontStyle, sf::Font> fonts;

    void loadFonts();
    const sf::Font &getFont(FontStyle style);
} // namespace FontManager
