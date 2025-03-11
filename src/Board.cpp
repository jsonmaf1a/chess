#include "Board.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/King.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Queen.hpp"
#include "pieces/Rook.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

Board::Board(sf::RenderTarget &target)
    : target(target)
{
    initializePieces();
}

void Board::draw()
{
    for(int row = 0; row < GRID_SIZE; row++)
    {
        for(int col = 0; col < GRID_SIZE; col++)
        {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition({col * CELL_SIZE * 1.0f, row * CELL_SIZE * 1.0f});
            cell.setFillColor(getCellColor(row + col));
            target.draw(cell);
        }
    }

    for(auto &piece : pieces)
    {
        piece->draw(target);
    }
}

void Board::initializePieces()
{
    // =============== Pawns =================
    for(int col = 0; col < GRID_SIZE; col++)
    {
        pieces.push_back(
            std::make_shared<Pawn>(sf::Vector2i(col, 6), PieceColor::White));
        pieces.push_back(
            std::make_shared<Pawn>(sf::Vector2i(col, 1), PieceColor::Black));
    }

    // =============== Rooks =================
    pieces.push_back(
        std::make_shared<Rook>(sf::Vector2i(0, 0), PieceColor::Black));
    pieces.push_back(
        std::make_shared<Rook>(sf::Vector2i(7, 0), PieceColor::Black));

    pieces.push_back(
        std::make_shared<Rook>(sf::Vector2i(0, 7), PieceColor::White));
    pieces.push_back(
        std::make_shared<Rook>(sf::Vector2i(7, 7), PieceColor::White));

    // =============== Knights ===============
    pieces.push_back(
        std::make_shared<Knight>(sf::Vector2i(1, 0), PieceColor::Black));
    pieces.push_back(
        std::make_shared<Knight>(sf::Vector2i(6, 0), PieceColor::Black));

    pieces.push_back(
        std::make_shared<Knight>(sf::Vector2i(1, 7), PieceColor::White));
    pieces.push_back(
        std::make_shared<Knight>(sf::Vector2i(6, 7), PieceColor::White));

    // =============== Bishops ===============
    pieces.push_back(
        std::make_shared<Bishop>(sf::Vector2i(2, 0), PieceColor::Black));
    pieces.push_back(
        std::make_shared<Bishop>(sf::Vector2i(5, 0), PieceColor::Black));

    pieces.push_back(
        std::make_shared<Bishop>(sf::Vector2i(2, 7), PieceColor::White));
    pieces.push_back(
        std::make_shared<Bishop>(sf::Vector2i(5, 7), PieceColor::White));

    // =============== Queens =================
    pieces.push_back(
        std::make_shared<Queen>(sf::Vector2i(3, 0), PieceColor::Black));
    pieces.push_back(
        std::make_shared<Queen>(sf::Vector2i(3, 7), PieceColor::White));

    // =============== Kings ==================
    pieces.push_back(
        std::make_shared<King>(sf::Vector2i(4, 0), PieceColor::Black));
    pieces.push_back(
        std::make_shared<King>(sf::Vector2i(4, 7), PieceColor::White));
}

sf::Color Board::getCellColor(int position)
{
    return position % 2 == 0 ? colorLight : colorDark;
};
