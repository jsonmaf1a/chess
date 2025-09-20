#pragma once

#include "GameData.hpp"
#include <chrono>
#include <optional>

using namespace std::chrono_literals;

struct Timer
{
    std::chrono::milliseconds millis = 0ms;

    void decrement(std::chrono::milliseconds value)
    {
        if(millis <= value)
        {
            millis = 0ms;
        }
        else
        {
            millis -= value;
        }
    }

    void increment(std::chrono::milliseconds value) { millis += value; }
};

struct TimeControl
{
    std::chrono::milliseconds duration;
    std::chrono::milliseconds increment = 0ms;

    TimeControl(std::chrono::seconds seconds,
                std::chrono::seconds incrementSec = 0s)
        : duration(
              std::chrono::duration_cast<std::chrono::milliseconds>(seconds))
        , increment(std::chrono::duration_cast<std::chrono::milliseconds>(
              incrementSec))
    {}
};

struct GamePreset
{
    GameMode gameMode;
    std::optional<TimeControl> timeControl = std::nullopt;
};

namespace GamePresets::Blitz
{
    static const auto _3min = GamePreset(GameMode::Blitz, TimeControl{3min});
    static const auto _3min_2s =
        GamePreset(GameMode::Blitz, TimeControl{3min, 2s});
    static const GamePreset _5min(GameMode::Blitz, TimeControl{1min * 5});
} // namespace GamePresets::Blitz

namespace GamePresets::Rapid
{
    static const GamePreset _10min(GameMode::Rapid, TimeControl{1min * 10});
    static const GamePreset _15min_10s(GameMode::Rapid,
                                       TimeControl{1min * 15, 1s * 10});
    static const GamePreset _30min(GameMode::Rapid, TimeControl{1min * 30});
} // namespace GamePresets::Rapid

namespace GamePresets::Classic
{
    static const GamePreset unlimited(GameMode::Classic);
    static const GamePreset _1h(GameMode::Classic, TimeControl{1h});
} // namespace GamePresets::Classic

namespace GamePresets::Bullet
{
    static const GamePreset _1min(GameMode::Bullet, TimeControl{1min});
    static const GamePreset _1min_1s(GameMode::Bullet, TimeControl{1min, 1s});
    static const GamePreset _2min_1s(GameMode::Bullet,
                                     TimeControl{1min * 2, 1s});

} // namespace GamePresets::Bullet

namespace GamePresets
{
    static constexpr GamePreset Custom(TimeControl timeControl)
    {
        return GamePreset(GameMode::Custom, timeControl);
    }
} // namespace GamePresets
