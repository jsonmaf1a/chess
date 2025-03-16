#pragma once

#include <SFML/Graphics/Color.hpp>

namespace ColorUtils
{
    static sf::Color dim(sf::Color color, float factor = 0.95f)
    {
        return sf::Color(color.r * factor, color.g * factor, color.b * factor,
                         color.a);
    }
} // namespace ColorUtils
