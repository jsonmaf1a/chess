#include "Piece.hpp"
#include "Board.hpp"
#include "utils/TextureManager.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

Piece::Piece(PieceType type, sf::Vector2i position, PieceColor color)
    : position(position)
    , color(color)
    , type(type)
    , texture(TextureManager::getTexture(getPieceTexturePath(type, color)))
    , sprite(texture)
{
    sprite.setTexture(texture, true);
    sprite.setScale({SCALE, SCALE});

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({bounds.size.x / 2.0f, bounds.size.y / 2.0f});

    sf::Vector2f spritePosition = calculateSpritePosition(position);
    sprite.setPosition(spritePosition);
}

void Piece::draw(sf::RenderTarget &target) const
{
    target.draw(sprite);
};

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
    float posX = static_cast<float>(position.x * Board::CELL_SIZE +
                                    Board::CELL_SIZE / 2.0f);
    float posY = static_cast<float>(position.y * Board::CELL_SIZE +
                                    Board::CELL_SIZE / 2.0f +
                                    Board::CELL_SIZE * yOffsetFactor);

    return sf::Vector2f(posX, posY);
}

bool Piece::isValidMove(sf::Vector2i newPosition) const
{
    auto moves = getValidMoves();
    auto it = std::find(moves.begin(), moves.end(), newPosition);

    return it != moves.end();
};

sf::Vector2i Piece::getPosition() const
{
    return position;
}

PieceColor Piece::getColor() const
{
    return color;
}

std::string Piece::getPieceTexturePath(PieceType type, PieceColor color)
{
    return std::format("{}/{}/{}.png", BASE_TEXTURES_PATH,
                       (color == PieceColor::White ? "white" : "black"),
                       pieceTypeToString(type));
}

std::string Piece::pieceTypeToString(PieceType type)
{
    switch(type)
    {
        case PieceType::Pawn:
            return "pawn";
        case PieceType::Knight:
            return "knight";
        case PieceType::Bishop:
            return "bishop";
        case PieceType::Rook:
            return "rook";
        case PieceType::Queen:
            return "queen";
        case PieceType::King:
            return "king";
        default:
            return "unknown";
    }
}
