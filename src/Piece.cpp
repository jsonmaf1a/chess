#include "Piece.hpp"
#include "Board.hpp"
#include "managers/TextureManager.hpp"
#include "managers/TransitionManager.hpp"
#include "shared/Notation.hpp"
#include "shared/PropertyTransition.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>
#include <math.h>

Piece::Piece(PieceKind kind, sf::Vector2i position, Side side)
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
    sprite.setOrigin({spriteBounds.size.x / 2.0f, spriteBounds.size.y / 2.0f});

    setPosition(sf::Vector2f(position));
}

void Piece::drawSelf(sf::RenderWindow &window) { window.draw(sprite); };

void Piece::setPosition(sf::Vector2f position)
{
    this->currentPosition = position;
    sprite.setPosition(normalizeSpritePosition(position));
}

void Piece::updatePositionWithTransition(sf::Vector2f position)
{
    auto positionTransition =
        std::make_shared<PropertyTransition<sf::Vector2f>>(
            currentPosition, position, 0.5f,
            [&](sf::Vector2f newPosition) { setPosition(newPosition); });

    TransitionManager::addTransition(positionTransition);
}

sf::Vector2f Piece::normalizeSpritePosition(sf::Vector2f position) const
{
    float posX =
        std::round(position.x * Board::CELL_SIZE + Board::CELL_SIZE / 2.0f);
    float posY =
        std::round(position.y * Board::CELL_SIZE + Board::CELL_SIZE / 2.0f);

    return {posX, posY};
}

bool Piece::isLegalMove(std::vector<std::shared_ptr<Piece>> onBoard,
                        sf::Vector2i newPosition) const
{
    auto moves = getLegalMoves(onBoard);
    auto it = std::find(moves.begin(), moves.end(), newPosition);

    return it != moves.end();
};

sf::Vector2f Piece::getPosition() const { return currentPosition; }

std::string Piece::getPieceTexturePath(PieceKind kind, Side side)
{
    return std::format("{}/{}/{}.png", BASE_TEXTURES_PATH,
                       (side == Side::White ? "white" : "black"),
                       getStringifiedKind());
}

std::string_view Piece::getStringifiedKind()
{
    return Piece::pieceKindToString(kind);
}

std::string_view Piece::pieceKindToString(PieceKind kind)
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

void Piece::printLegalMoves(std::vector<std::shared_ptr<Piece>> onBoard) const
{
    std::cout << "\n"
              << "Current legal moves for ";
    printSelf();
    std::cout << ":";

    auto moves = getLegalMoves(onBoard);

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
              << pieceKindToString(kind);
}
