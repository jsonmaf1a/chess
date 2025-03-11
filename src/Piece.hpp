#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System.hpp>

#include <SFML/System/Vector2.hpp>
#include <vector>

enum class PieceType
{
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King,
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
    static constexpr const int SPRITE_SIZE = 64;
    static constexpr const float SCALE = 1.0f;
    static constexpr const char *BASE_TEXTURES_PATH =
        "./assets/textures/pieces/";

    const PieceType type;

    const float yOffsetFactor = 0.05f;

    PieceColor color;
    sf::Vector2i position;
    sf::Texture texture;
    sf::Sprite sprite;

    bool wasMoved = false;

    static std::string getPieceTexturePath(PieceType type, PieceColor color);

  public:
    Piece(PieceType type, sf::Vector2i position, PieceColor color);
    ~Piece() = default;

    virtual std::vector<sf::Vector2i> getValidMoves() const = 0;

    void draw(sf::RenderTarget &target) const;

    void moveTo(sf::Vector2i newPosition);
    bool isValidMove(sf::Vector2i newPosition) const;

    sf::Vector2i getPosition() const;
    PieceColor getColor() const;

  private:
    template <typename T>
    sf::Vector2f calculateSpritePosition(sf::Vector2<T> position) const;
    static std::string pieceTypeToString(PieceType type);
};
