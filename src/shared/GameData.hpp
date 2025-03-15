#pragma once

#include <string>

enum class Side
{
    White,
    Black,
};

enum class PieceType
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
    PieceType pieceType;
    std::string position;
};
