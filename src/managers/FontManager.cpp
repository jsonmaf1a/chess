#include "managers/FontManager.hpp"
#include <unordered_map>

namespace
{
    static std::unordered_map<FontStyle, sf::Font> fonts;
} // namespace

namespace FontManager
{
    void loadFonts()
    {
        const std::string BASE_PATH = "assets/fonts/static/";

        std::unordered_map<FontStyle, std::string> fontPaths = {
            {FontStyle::Regular, "Roboto-Regular.ttf"},
            {FontStyle::Light, "Roboto-Light.ttf"},
            {FontStyle::Medium, "Roboto-Medium.ttf"},
            {FontStyle::Semibold, "Roboto-SemiBold.ttf"},
            {FontStyle::Bold, "Roboto-Bold.ttf"}};

        for(const auto &[fontStyle, fontPath] : fontPaths)
        {
            if(!fonts[fontStyle].openFromFile(BASE_PATH + fontPath))
                throw std::runtime_error("Failed to load font: " + BASE_PATH +
                                         fontPath);
        }
    }

    const sf::Font &getFont(FontStyle style) { return fonts.at(style); }

} // namespace FontManager
