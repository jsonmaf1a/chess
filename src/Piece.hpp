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
    sf::Vector2i currentPosition;
    sf::Texture texture;
    sf::Sprite sprite;

    std::string getPieceTexturePath(PieceKind kind, Side side);

  public:
    Piece(PieceKind kind, sf::Vector2i position, Side side);
    ~Piece() = default;

    bool wasMoved = false;

    virtual void drawSelf(sf::RenderWindow &window) override;

    virtual std::vector<sf::Vector2i> getLegalMoves() const = 0;
    bool isLegalMove(sf::Vector2i newPosition) const;

    void setPosition(sf::Vector2i position);
    sf::Vector2i getPosition() const;
    Side getSide() const;
    PieceKind getKind() const;

    static std::string pieceKindToString(PieceKind kind);
    std::string pieceKindToString();
    sf::Vector2f normalizeSpritePosition(sf::Vector2i position) const;
};
