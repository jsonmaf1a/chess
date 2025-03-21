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

template <> constexpr std::string_view StringUtils::toString(Side side)
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

template <> constexpr std::string_view StringUtils::toString(PieceKind kind)
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

template <> constexpr char StringUtils::toChar(PieceKind kind)
{
    switch(kind)
    {
        case PieceKind::Pawn:
            return 'p';
        case PieceKind::Knight:
            return 'n';
        case PieceKind::Bishop:
            return 'b';
        case PieceKind::Rook:
            return 'r';
        case PieceKind::Queen:
            return 'q';
        case PieceKind::King:
            return 'k';
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

template <> constexpr std::string_view StringUtils::toString(GameMode mode)
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
    unsigned int millis;
    unsigned int incrementMillis = 0;
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
                                          TimeControl{60 * 60 * 1000});

    static const GameModePreset Rapid10(GameMode::Rapid,
                                        TimeControl{60 * 10 * 1000});
    static const GameModePreset Rapid15plus10(GameMode::Rapid,
                                              TimeControl{60 * 15 * 1000,
                                                          10 * 1000});
    static const GameModePreset Rapid30(GameMode::Rapid,
                                        TimeControl{60 * 30 * 1000});

    static const GameModePreset Blitz3(GameMode::Blitz,
                                       TimeControl{60 * 3 * 1000});
    static const GameModePreset Blitz3plus2(GameMode::Blitz,
                                            TimeControl{60 * 3 * 1000,
                                                        2 * 1000});
    static const GameModePreset Blitz5(GameMode::Blitz,
                                       TimeControl{60 * 5 * 1000});

    static const GameModePreset Bullet1(GameMode::Bullet,
                                        TimeControl{60 * 1 * 1000});
    static const GameModePreset Bullet1plus1(GameMode::Bullet,
                                             TimeControl{60 * 1 * 1000,
                                                         1 * 1000});
    static const GameModePreset Bullet2plus1(GameMode::Bullet,
                                             TimeControl{60 * 2 * 1000,
                                                         1 * 1000});

    static constexpr GameModePreset Custom(TimeControl timeControl)
    {
        return GameModePreset(GameMode::Custom, timeControl);
    }
} // namespace GameModePresets
