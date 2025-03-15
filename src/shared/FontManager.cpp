#include "FontManager.hpp"
#include <unordered_map>

namespace
{
    static std::unordered_map<FontStyle, sf::Font> fonts;
}

namespace FontManager
{
    void loadFonts()
    {
        const std::unordered_map<FontStyle, std::string> fontPaths = {
            {FontStyle::Regular, "assets/fonts/static/Roboto-Regular.ttf"},
            {FontStyle::Light, "assets/fonts/static/Roboto-Light.ttf"},
            {FontStyle::Medium, "assets/fonts/static/Roboto-Medium.ttf"},
            {FontStyle::Semibold, "assets/fonts/static/Roboto-SemiBold.ttf"},
            {FontStyle::Bold, "assets/fonts/static/Roboto-Bold.ttf"}};

        for(const auto &[style, path] : fontPaths)
        {
            if(!fonts[style].openFromFile(path))
                throw std::runtime_error("Failed to load font: " + path);
        }
    }

    const sf::Font &getFont(FontStyle style) { return fonts.at(style); }

} // namespace FontManager
