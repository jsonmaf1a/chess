#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>

namespace FontUtils
{
    static float getBaselineOffset(const sf::Font &font,
                                   const unsigned int characterSize,
                                   const std::string &text)
    {
        // We'll use the line spacing to determine the fixed offset
        float lineSpacing = font.getLineSpacing(characterSize);

        // A small buffer to ensure the text stays visually centered (you can
        // adjust this buffer as needed)
        return -lineSpacing * 0.25f;
    };
} // namespace FontUtils
