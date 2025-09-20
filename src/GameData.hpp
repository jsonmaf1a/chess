#pragma once

#include <string_view>
#include <utility>
#include <wisp/utils/StringUtils.hpp>

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
