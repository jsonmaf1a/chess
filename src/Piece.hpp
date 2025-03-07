#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <algorithm>
#include <vector>

enum class PieceType
{
  Pawn,
  Rook,
  Knight,
  Bishop,
  Queen,
  King,
  None
};
enum class PieceColor
{
  White,
  Black,
  Unknown
};

class Piece
{
protected:
  PieceColor color;
  sf::Vector2i position;
  sf::Sprite sprite;

  bool wasMoved = false;

  static constexpr int SPRITE_SIZE = 64;

public:
  Piece(sf::Vector2i position, PieceColor color, const sf::Texture &texture)
      : position(position), color(color), sprite(texture)
  {
    sprite.setPosition({static_cast<float>(position.x * 64), static_cast<float>(position.y * 64)});
  };
  virtual ~Piece() = default;

  // NOTE: (color == PieceColor::White && position.y == 6) || (color == PieceColor::Black && position.y == 1)
  virtual std::vector<sf::Vector2i> getValidMoves() const = 0;

  virtual void draw(sf::RenderWindow &window) const
  {
    window.draw(sprite);
  };

  virtual void moveTo(sf::Vector2i newPosition)
  {
    position = newPosition;
    sprite.setPosition(
        {static_cast<float>(newPosition.x * SPRITE_SIZE), static_cast<float>(newPosition.y * SPRITE_SIZE)});
    wasMoved = true;
  };

  bool isValidMove(sf::Vector2i newPosition) const
  {
    auto moves = getValidMoves();
    auto it = std::find(moves.begin(), moves.end(), newPosition);

    return it != moves.end();
  };

  sf::Vector2i getPosition() const
  {
    return position;
  }

  PieceColor getColor() const
  {
    return color;
  }

  bool isInInitialPosition() const
  {
    return !wasMoved;
  };
};
