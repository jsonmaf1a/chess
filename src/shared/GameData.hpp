#pragma once

#include <string>

enum class Side
{
    White,
    Black,
};

enum class PieceKind
{
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King,
};

struct Move
{
  public:
    Side player;
    PieceKind pieceKind;
    std::string position;
};
