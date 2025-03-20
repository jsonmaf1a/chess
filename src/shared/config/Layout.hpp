#pragma once

#include <SFML/Graphics/Rect.hpp>

namespace LayoutConfig
{
    static constexpr sf::Vector2u WindowBounds{1200, 800};
    static constexpr sf::Vector2f WindowViewport{1.f, 1.f};

    static constexpr sf::FloatRect SidebarBounds{
        {0, 0}, {WindowBounds.x / 3.f, WindowBounds.y}};

    static constexpr sf::FloatRect SidebarViewport{
        {0.f, 0.f}, {WindowViewport.x / 3.f, WindowViewport.y}};

    static constexpr sf::FloatRect BoardBounds{
        {0, 0}, {WindowBounds.y, WindowBounds.y}};

    static constexpr sf::FloatRect BoardViewport{
        {WindowViewport.x / 3.f, 0.f},
        {WindowViewport.x - WindowViewport.x / 3.f, WindowViewport.y}};
} // namespace LayoutConfig
