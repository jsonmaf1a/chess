#include "Board.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/King.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Queen.hpp"
#include "pieces/Rook.hpp"
#include "shared/Notation.hpp"
#include <iostream>

Board::Board(sf::RenderWindow &target, sf::FloatRect bounds,
             sf::FloatRect viewport)
    : UIComponent(bounds)
{
    view.setViewport(viewport);

    initializePieces();
}

void Board::drawSelf(sf::RenderWindow &window)
{
    window.setView(view);

    for(int row = 0; row < GRID_SIZE; row++)
    {
        for(int col = 0; col < GRID_SIZE; col++)
        {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition({col * CELL_SIZE, row * CELL_SIZE});

            sf::Color cellColor = getCellColor(row + col);

            if(row == hoveredRow && col == hoveredCol)
            {
                cellColor.r = std::min(255, cellColor.r - 10);
                cellColor.g = std::min(255, cellColor.g - 10);
                cellColor.b = std::min(255, cellColor.b - 10);
            }

            cell.setFillColor(cellColor);
            window.draw(cell);
        }
    }

    drawLabels();
}

void drawLabels() {}

EventResult Board::handleSelfEvent(const EventContext &eventCtx)
{
    if(eventCtx.event.is<sf::Event::MouseMoved>())
    {
        const auto mouseMoved = eventCtx.event.getIf<sf::Event::MouseMoved>();
        const auto &window = eventCtx.window;
        auto &cursorManager = eventCtx.cursorManager;

        const auto mousePos = mouseMoved->position;

        sf::Vector2f normalizedMousePos =
            getNormalizedMousePosition(mousePos, window);

        if(!isMouseOverViewport(normalizedMousePos))
        {
            cursorManager.resetCursor();
            resetHoveredCell();

            return EventResult::Handled;
        }

        sf::Vector2f localMousePos = window.mapPixelToCoords(mousePos, view);

        int col = localMousePos.x / CELL_SIZE;
        int row = localMousePos.y / CELL_SIZE;

        if(isMouseOverCell({col, row}))
        {
            cursorManager.setHandCursor();
            setHoveredCell({row, col});

            std::cout << "Board mousemove: "
                      << "row: " << row << "\t"
                      << "col: " << col << "\n";

            return EventResult::Consumed;
        }
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
    static constexpr const int WHITE_PAWNS_ROW = 2;
    static constexpr const int BLACK_PAWNS_ROW = 7;

    // =============== Pawns =================
    for(char file = 'A'; file <= 'H'; file++)
    {
        pieces.push_back(
            std::make_shared<Pawn>(Notation::fromChessNotation(std::format(
                                       "{}{}", file, WHITE_PAWNS_ROW)),
                                   PieceColor::White));
        pieces.push_back(
            std::make_shared<Pawn>(Notation::fromChessNotation(std::format(
                                       "{}{}", file, BLACK_PAWNS_ROW)),
                                   PieceColor::Black));
    }

    // =============== Rooks =================
    pieces.push_back(std::make_shared<Rook>(Notation::fromChessNotation("A1"),
                                            PieceColor::White));
    pieces.push_back(std::make_shared<Rook>(Notation::fromChessNotation("H1"),
                                            PieceColor::White));
    pieces.push_back(std::make_shared<Rook>(Notation::fromChessNotation("A8"),
                                            PieceColor::Black));
    pieces.push_back(std::make_shared<Rook>(Notation::fromChessNotation("H8"),
                                            PieceColor::Black));

    // =============== Knights ===============
    pieces.push_back(std::make_shared<Knight>(Notation::fromChessNotation("B1"),
                                              PieceColor::White));
    pieces.push_back(std::make_shared<Knight>(Notation::fromChessNotation("G1"),
                                              PieceColor::White));
    pieces.push_back(std::make_shared<Knight>(Notation::fromChessNotation("B8"),
                                              PieceColor::Black));
    pieces.push_back(std::make_shared<Knight>(Notation::fromChessNotation("G8"),
                                              PieceColor::Black));

    // =============== Bishops ===============
    pieces.push_back(std::make_shared<Bishop>(Notation::fromChessNotation("C1"),
                                              PieceColor::White));
    pieces.push_back(std::make_shared<Bishop>(Notation::fromChessNotation("F1"),
                                              PieceColor::White));
    pieces.push_back(std::make_shared<Bishop>(Notation::fromChessNotation("C8"),
                                              PieceColor::Black));
    pieces.push_back(std::make_shared<Bishop>(Notation::fromChessNotation("F8"),
                                              PieceColor::Black));

    // =============== Queens =================
    pieces.push_back(std::make_shared<Queen>(Notation::fromChessNotation("D1"),
                                             PieceColor::White));
    pieces.push_back(std::make_shared<Queen>(Notation::fromChessNotation("D8"),
                                             PieceColor::Black));

    // =============== Kings ==================
    pieces.push_back(std::make_shared<King>(Notation::fromChessNotation("E1"),
                                            PieceColor::White));
    pieces.push_back(std::make_shared<King>(Notation::fromChessNotation("E8"),
                                            PieceColor::Black));
}

sf::Color Board::getCellColor(int cellPosition) const
{
    return cellPosition % 2 == 0 ? colorCellLight : colorCellDark;
};

void Board::setHoveredCell(sf::Vector2i position)
{
    hoveredRow = position.x;
    hoveredCol = position.y;
};

void Board::resetHoveredCell()
{
    hoveredRow = -1;
    hoveredCol = -1;
};

bool Board::isMouseOverCell(sf::Vector2i mousePos)
{
    int col = mousePos.x / CELL_SIZE;
    int row = mousePos.y / CELL_SIZE;

    return row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE;
}

sf::Vector2f Board::getNormalizedMousePosition(const sf::Vector2i &mousePos,
                                               const sf::RenderWindow &window)
{
    return {static_cast<float>(mousePos.x) / window.getSize().x,
            static_cast<float>(mousePos.y) / window.getSize().y};
}
