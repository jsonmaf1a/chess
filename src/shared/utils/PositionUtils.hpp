#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
namespace PositionUtils
{
    static inline sf::Vector2f getNormalizedMousePosition(
        const sf::Vector2i &mousePos, const sf::RenderWindow &window)
    {
        return {static_cast<float>(mousePos.x) / window.getSize().x,
                static_cast<float>(mousePos.y) / window.getSize().y};
    }
} // namespace PositionUtils
