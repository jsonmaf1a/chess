#pragma once

#include "GameData.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <wisp/core/Component.hpp>

class Board;

// TODO: drag & drop
class Piece : public Component
{
  protected:
    const PieceKind kind;
    const Side side;
    sf::Vector2i currentPosition;
    sf::Texture texture;
    sf::Sprite sprite;

    std::string getTexturePath(PieceKind kind, Side side);

  public:
    Piece(PieceKind kind, Side side, sf::Vector2i position);
    ~Piece() = default;

    bool hasMoved = false;

    virtual void drawSelf(sf::RenderWindow &window) override;

    virtual std::vector<sf::Vector2i> getLegalMoves() const = 0;
    virtual std::vector<sf::Vector2i> getValidMoves(Board &board) const = 0;
    bool isLegalMove(sf::Vector2i newPosition) const;

    void updatePositionWithTransition(sf::Vector2i position);
    void setPosition(sf::Vector2i position);
    sf::Vector2i getPosition() const;

    template <typename T>
        requires std::is_arithmetic_v<T>
    sf::Vector2f normalizeSpritePosition(sf::Vector2<T> position) const;

    Side getSide() const;
    PieceKind getKind() const;

    void printLegalMoves() const;
    void printSelf() const;

  private:
    static constexpr float SPRITE_SIZE = 100.f;
};
