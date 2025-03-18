#include "Piece.hpp"
#include "Board.hpp"
#include "managers/TextureManager.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <math.h>

// TODO: get rid of position
Piece::Piece(PieceKind kind, sf::Vector2i position, Side side)
    : UIComponent({SPRITE_SIZE, SPRITE_SIZE})
    , currentPosition(position)
    , side(side)
    , kind(kind)
    , texture(TextureManager::getTexture(getPieceTexturePath(kind, side)))
    , sprite(texture)
{
    sprite.setTexture(texture, true);
    sprite.setScale({SCALE, SCALE});

    sf::FloatRect spriteBounds = sprite.getLocalBounds();
    sprite.setOrigin({spriteBounds.size.x / 2.0f, spriteBounds.size.y / 2.0f});

    setPosition(position);
}

void Piece::drawSelf(sf::RenderWindow &window) { window.draw(sprite); };

void Piece::setPosition(sf::Vector2i position)
{
    this->currentPosition = position;

    sf::Vector2f spritePosition = normalizeSpritePosition(position);
    sprite.setPosition(spritePosition);
}

sf::Vector2f Piece::normalizeSpritePosition(sf::Vector2i position) const
{
    float posX =
        std::round(position.x * Board::CELL_SIZE + Board::CELL_SIZE / 2.0f);
    float posY =
        std::round(position.y * Board::CELL_SIZE + Board::CELL_SIZE / 2.0f);

    return sf::Vector2f(posX, posY);
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
                       pieceKindToString());
}

std::string Piece::pieceKindToString()
{
    return Piece::pieceKindToString(kind);
}

std::string Piece::pieceKindToString(PieceKind kind)
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
