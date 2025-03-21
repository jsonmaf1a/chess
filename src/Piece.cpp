#include "Piece.hpp"
#include "managers/TextureManager.hpp"
#include "managers/TransitionManager.hpp"
#include "shared/Notation.hpp"
#include "shared/PropertyTransition.hpp"
#include "shared/config/Board.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include <math.h>

Piece::Piece(PieceKind kind, Side side, sf::Vector2i position)
    : UIComponent({SPRITE_SIZE, SPRITE_SIZE})
    , currentPosition(position)
    , kind(kind)
    , side(side)
    , texture(TextureManager::getTexture(getPieceTexturePath(kind, side)))
    , sprite(texture)
{
    sprite.setTexture(texture, true);
    sprite.setScale({SPRITE_SCALE, SPRITE_SCALE});

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

std::string Piece::getPieceTexturePath(PieceKind kind, Side side)
{
    return std::format("{}/{}/{}.png", BASE_TEXTURES_PATH,
                       (side == Side::White ? "white" : "black"),
                       getStringifiedKind());
}

std::string_view Piece::getStringifiedKind() const
{
    return StringUtils::toString(kind);
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
              << getStringifiedKind();
}
