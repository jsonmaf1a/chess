#include "FontManager.hpp"

void FontManager::loadFonts()
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

const sf::Font &FontManager::getFont(FontStyle style)
{
    return fonts.at(style);
}
