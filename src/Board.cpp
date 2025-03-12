#include "Board.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/King.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Queen.hpp"
#include "pieces/Rook.hpp"
#include <iostream>

Board::Board(sf::FloatRect bounds, sf::RenderWindow &target)
    : boardView(bounds)
    , UIComponent(bounds)
{
    boardView.setViewport(sf::FloatRect({0.3f, 0.f}, {0.7f, 1.f}));

    initializePieces();
}

void Board::drawSelf(sf::RenderWindow &window)
{
    for(int row = 0; row < GRID_SIZE; row++)
    {
        for(int col = 0; col < GRID_SIZE; col++)
        {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition({col * CELL_SIZE * 1.0f, row * CELL_SIZE * 1.0f});
            cell.setFillColor(getCellColor(row + col));

            window.draw(cell);
        }
    }
}

EventResult Board::handleSelfEvent(const sf::Event &event)
{
    if(event.is<sf::Event::MouseMoved>())
    {
        const auto mouseMoved = event.getIf<sf::Event::MouseMoved>();
        std::cout << "MouseMove event: "
                  << "x: " << mouseMoved->position.x << "\t"
                  << "y: " << mouseMoved->position.y << "\n";
        return EventResult::Handled;
    }
    else
    {
        std::cout << "penis" << "\n";
    }

    return EventResult::Ignored;
}

void Board::initializePieces()
{
    createPieces();

    for(auto &piece : pieces)
    {
        addChild(piece);
    }
}

void Board::createPieces()
{
    // =============== Pawns =================
    for(char file = 'A'; file <= 'H'; file++)
    {
        pieces.emplace_back(std::make_shared<Pawn>(
            fromChessNotation(std::format("{}2", file)), PieceColor::White));
        pieces.emplace_back(std::make_shared<Pawn>(
            fromChessNotation(std::format("{}7", file)), PieceColor::Black));
    }

    // =============== Rooks =================
    pieces.push_back(
        std::make_shared<Rook>(fromChessNotation("A1"), PieceColor::White));
    pieces.push_back(
        std::make_shared<Rook>(fromChessNotation("H1"), PieceColor::White));
    pieces.push_back(
        std::make_shared<Rook>(fromChessNotation("A8"), PieceColor::Black));
    pieces.push_back(
        std::make_shared<Rook>(fromChessNotation("H8"), PieceColor::Black));

    // =============== Knights ===============
    pieces.push_back(
        std::make_shared<Knight>(fromChessNotation("B1"), PieceColor::White));
    pieces.push_back(
        std::make_shared<Knight>(fromChessNotation("G1"), PieceColor::White));
    pieces.push_back(
        std::make_shared<Knight>(fromChessNotation("B8"), PieceColor::Black));
    pieces.push_back(
        std::make_shared<Knight>(fromChessNotation("G8"), PieceColor::Black));

    // =============== Bishops ===============
    pieces.push_back(
        std::make_shared<Bishop>(fromChessNotation("C1"), PieceColor::White));
    pieces.push_back(
        std::make_shared<Bishop>(fromChessNotation("F1"), PieceColor::White));
    pieces.push_back(
        std::make_shared<Bishop>(fromChessNotation("C8"), PieceColor::Black));
    pieces.push_back(
        std::make_shared<Bishop>(fromChessNotation("F8"), PieceColor::Black));

    // =============== Queens =================
    pieces.push_back(
        std::make_shared<Queen>(fromChessNotation("D1"), PieceColor::White));
    pieces.push_back(
        std::make_shared<Queen>(fromChessNotation("D8"), PieceColor::Black));

    // =============== Kings ==================
    pieces.push_back(
        std::make_shared<King>(fromChessNotation("E1"), PieceColor::White));
    pieces.push_back(
        std::make_shared<King>(fromChessNotation("E8"), PieceColor::Black));
}

sf::Color Board::getCellColor(int cellPosition) const
{
    return cellPosition % 2 == 0 ? colorCellLight : colorCellDark;
};

sf::Vector2f Board::mapToViewCoords(sf::RenderWindow &renderWindow,
                                    sf::Vector2i mousePos)
{
    return renderWindow.mapPixelToCoords(mousePos, boardView);
}

std::string Board::toChessNotation(const sf::Vector2i &position) const
{
    char file = 'A' + position.x;
    char rank = '1' + (7 - position.y);

    return std::string(1, file) + rank;
}

sf::Vector2i Board::fromChessNotation(const std::string &notation) const
{
    if(notation.length() != 2)
        throw std::invalid_argument("Invalid notation");

    int x = notation[0] - 'A';
    int y = 7 - (notation[1] - '1');

    return {x, y};
}
