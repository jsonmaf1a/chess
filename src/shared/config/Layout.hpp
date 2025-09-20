#pragma once

#include <SFML/Graphics/Rect.hpp>

namespace LayoutConfig
{
    static constexpr sf::Vector2f WindowSize{1100.f, 800.f};
    static constexpr sf::Vector2f WindowViewport{1.f, 1.f};

    static constexpr sf::FloatRect SidebarBounds{{0.f, 0.f},
                                                 {300.f, WindowSize.y}};

    static constexpr sf::FloatRect SidebarViewport{
        {0.f, 0.f}, {300.f / WindowSize.x, WindowViewport.y}};

    static constexpr sf::FloatRect BoardBounds{{0.f, 0.f},
                                               {WindowSize.y, WindowSize.y}};

    static constexpr sf::FloatRect BoardViewport{
        {SidebarViewport.size.x, 0.f},
        {WindowViewport.x - (300.f / WindowSize.x), WindowViewport.y}};
} // namespace LayoutConfig
