#pragma once

#include "shared/GameData.hpp"
#include "shared/UIComponent.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>

class Piece : public UIComponent
{
  protected:
    static constexpr int SPRITE_SIZE = 100;
    static constexpr float SCALE = 1.0f;
    static constexpr const char *BASE_TEXTURES_PATH =
        "./assets/textures/pieces/";

    const PieceKind kind;

    Side side;
    sf::Vector2i position;
    sf::Texture texture;
    sf::Sprite sprite;

    bool wasMoved = false;

    static std::string getPieceTexturePath(PieceKind kind, Side side);

  public:
    Piece(PieceKind kind, sf::Vector2i position, Side side);
    ~Piece() = default;

    virtual std::vector<sf::Vector2i> getValidMoves() const = 0;

    virtual void drawSelf(sf::RenderWindow &window) override;
    bool isValidMove(sf::Vector2i newPosition) const;

    // NOTE: consider moving this to the board
    void moveTo(sf::Vector2i newPosition);

    sf::Vector2i getPosition() const;
    Side getSide() const;
    PieceKind getKind() const;
    static std::string pieceTypeToString(PieceKind kind);

  private:
    template <typename T>
    sf::Vector2f calculateSpritePosition(sf::Vector2<T> position) const;
};
