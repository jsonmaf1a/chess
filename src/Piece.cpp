#include "Piece.hpp"
#include "Board.hpp"
#include "shared/TextureManager.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <math.h>

Piece::Piece(PieceKind kind, sf::Vector2i position, Side side)
    : position(position)
    , side(side)
    , kind(kind)
    , texture(TextureManager::getTexture(getPieceTexturePath(kind, side)))
    , sprite(texture)
    , UIComponent(sf::FloatRect({0, 0}, {SPRITE_SIZE, SPRITE_SIZE}))
{
    sprite.setTexture(texture, true);
    sprite.setScale({SCALE, SCALE});

    sf::FloatRect spriteBounds = sprite.getLocalBounds();
    sprite.setOrigin({spriteBounds.size.x / 2.0f, spriteBounds.size.y / 2.0f});

    sf::Vector2f spritePosition = calculateSpritePosition(position);
    sprite.setPosition(spritePosition);
}

void Piece::drawSelf(sf::RenderWindow &window) { window.draw(sprite); };

void Piece::moveTo(sf::Vector2i newPosition)
{
    position = newPosition;

    sf::Vector2f spritePosition = calculateSpritePosition(newPosition);
    sprite.setPosition(spritePosition);

    wasMoved = true;
}

template <typename T>
sf::Vector2f Piece::calculateSpritePosition(sf::Vector2<T> position) const
{
    float posX =
        std::round(position.x * Board::CELL_SIZE + Board::CELL_SIZE / 2.0f);
    float posY =
        std::round(position.y * Board::CELL_SIZE + Board::CELL_SIZE / 2.0f);

    return sf::Vector2f(posX, posY);
}

bool Piece::isValidMove(sf::Vector2i newPosition) const
{
    auto moves = getValidMoves();
    auto it = std::find(moves.begin(), moves.end(), newPosition);

    return it != moves.end();
};

sf::Vector2i Piece::getPosition() const { return position; }

std::string Piece::getPieceTexturePath(PieceKind kind, Side side)
{
    return std::format("{}/{}/{}.png", BASE_TEXTURES_PATH,
                       (side == Side::White ? "white" : "black"),
                       pieceTypeToString(kind));
}

std::string Piece::pieceTypeToString(PieceKind kind)
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
            return "unknown";
    }
}

Side Piece::getSide() const { return side; }

PieceKind Piece::getKind() const { return kind; }
