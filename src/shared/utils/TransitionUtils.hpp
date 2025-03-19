
#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace TransitionUtils
{

    template <typename T> static constexpr T lerp(T a, T b, float t)
    {
        return a + (b - a) * t;
    }

    static constexpr float smoothstep(float t)
    {
        return t * t * (3.f - 2.f * t);
    }

    static constexpr sf::Vector2f smoothLerp(sf::Vector2f a, sf::Vector2f b,
                                             float t)
    {
        t = smoothstep(t);
        return lerp(a, b, t);
    }

    static constexpr sf::Vector2f expLerp(sf::Vector2f a, sf::Vector2f b,
                                          float t, float k = 10.0f)
    {
        t = (1.0f - std::exp(-k * t));
        return lerp(a, b, t);
    }

} // namespace TransitionUtils
