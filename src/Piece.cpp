#include "Piece.hpp"
#include "Notation.hpp"
#include "config/Board.hpp"
#include "managers/TextureManager.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include <math.h>
#include <wisp/core/managers/TransitionManager.hpp>
#include <wisp/transitions/PropertyTransition.hpp>

Piece::Piece(PieceKind kind, Side side, sf::Vector2i position)
    : Component({BoardConfig::CellSize, BoardConfig::CellSize})
    , currentPosition(position)
    , kind(kind)
    , side(side)
    , texture(TextureManager::getTexture(getTexturePath(kind, side)))
    , sprite(texture)
{
    sprite.setTexture(texture, true);

    float scaleFactor = BoardConfig::CellSize / SPRITE_SIZE;

    sprite.setScale({scaleFactor, scaleFactor});

    sf::FloatRect spriteBounds = sprite.getLocalBounds();
    sprite.setOrigin({spriteBounds.size.x / 2.f, spriteBounds.size.y / 2.f});

    setPosition(position);
}

void Piece::drawSelf(sf::RenderWindow &window) { window.draw(sprite); };

void Piece::setPosition(sf::Vector2i position)
{
    this->currentPosition = position;
    sprite.setPosition(normalizeSpritePosition(position));
}

void Piece::updatePositionWithTransition(sf::Vector2i position)
{
    float transitionDurationSecs = 0.5f;
    auto positionTransition =
        std::make_shared<PropertyTransition<sf::Vector2f>>(
            static_cast<sf::Vector2f>(currentPosition),
            static_cast<sf::Vector2f>(position), transitionDurationSecs,
            [this](sf::Vector2f newPosition) {
                sprite.setPosition(normalizeSpritePosition(newPosition));
            });
    TransitionManager::addTransition(positionTransition);

    this->currentPosition = position;
}

template <typename T>
    requires std::is_arithmetic_v<T>
sf::Vector2f Piece::normalizeSpritePosition(sf::Vector2<T> position) const
{
    float posX = std::round(position.x * BoardConfig::CellSize +
                            BoardConfig::CellSize / 2.0f);
    float posY = std::round(position.y * BoardConfig::CellSize +
                            BoardConfig::CellSize / 2.0f);

    return {posX, posY};
}

bool Piece::isLegalMove(sf::Vector2i newPosition) const
{
    auto moves = getLegalMoves();
    auto it = std::find(moves.begin(), moves.end(), newPosition);

    return it != moves.end();
};

sf::Vector2i Piece::getPosition() const { return currentPosition; }

std::string Piece::getTexturePath(PieceKind kind, Side side)
{
    const char *BASE_TEXTURES_PATH = "./assets/textures/pieces";

    return std::format("{}/x{}/{}/{}.png", BASE_TEXTURES_PATH, SPRITE_SIZE,
                       StringUtils::toString(side),
                       StringUtils::toString(kind));
}

Side Piece::getSide() const { return side; }

PieceKind Piece::getKind() const { return kind; }

void Piece::printLegalMoves() const
{
    std::cout << "\n"
              << "Current legal moves for ";
    printSelf();
    std::cout << ":";

    auto moves = getLegalMoves();

    for(auto move : moves)
    {
        std::cout << Notation::toChessNotation(move)
                  << (move == moves.back() ? ". " : ", ");
    }
    std::cout << "\n";
};

void Piece::printSelf() const
{
    std::cout << (side == Side::White ? "white" : "black") << " "
              << StringUtils::toString(kind);
}
