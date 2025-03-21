#pragma once

#include "utils/StringUtils.hpp"
#include <optional>
#include <string_view>
#include <utility>

enum class Side
{
    White,
    Black,
};

template <> constexpr std::string_view StringUtils::stringify(Side side)
{
    switch(side)
    {
        case Side::White:
            return "white";
        case Side::Black:
            return "black";
        default:
            std::unreachable();
    }
}

enum class PieceKind
{
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King,
};

template <> constexpr std::string_view StringUtils::stringify(PieceKind kind)
{
    switch(kind)
    {
        case PieceKind::Pawn:
            return "pawn";
        case PieceKind::Knight:
            return "knight";
        case PieceKind::Bishop:
            return "bishop";
        case PieceKind::Rook:
            return "rook";
        case PieceKind::Queen:
            return "queen";
        case PieceKind::King:
            return "king";
        default:
            std::unreachable();
    }
}

enum class GameMode
{
    Classic,
    Rapid,
    Blitz,
    Bullet,
    Custom
};

template <> constexpr std::string_view StringUtils::stringify(GameMode mode)
{
    switch(mode)
    {
        case GameMode::Classic:
            return "classic";
        case GameMode::Rapid:
            return "rapid";
        case GameMode::Blitz:
            return "blitz";
        case GameMode::Bullet:
            return "bullet";
        case GameMode::Custom:
            return "custom";
        default:
            std::unreachable();
    }
}

struct TimeControl
{
    unsigned int secondsRemain;
    unsigned int incrementPerMove = 0;
};

struct GameModePreset
{
    GameMode gameMode;
    std::optional<TimeControl> timeControl = std::nullopt;
};

namespace GameModePresets
{
    static const GameModePreset ClassicUnlimited(GameMode::Classic);
    static const GameModePreset Classic60(GameMode::Classic,
                                          TimeControl{60 * 60});

    static const GameModePreset Rapid10(GameMode::Rapid, TimeControl{60 * 10});
    static const GameModePreset Rapid15plus10(GameMode::Rapid,
                                              TimeControl{60 * 15, 10});
    static const GameModePreset Rapid30(GameMode::Rapid, TimeControl{60 * 30});

    static const GameModePreset Blitz3(GameMode::Blitz, TimeControl{60 * 3});
    static const GameModePreset Blitz3plus2(GameMode::Blitz,
                                            TimeControl{60 * 3, 2});
    static const GameModePreset Blitz5(GameMode::Blitz, TimeControl{60 * 5});

    static const GameModePreset Bullet1(GameMode::Bullet, TimeControl{60 * 1});
    static const GameModePreset Bullet1plus1(GameMode::Bullet,
                                             TimeControl{60 * 1, 1});
    static const GameModePreset Bullet2plus1(GameMode::Bullet,
                                             TimeControl{60 * 2, 1});

    static constexpr GameModePreset createCustomPreset(TimeControl timeControl)
    {
        return GameModePreset(GameMode::Custom, timeControl);
    }
} // namespace GameModePresets
