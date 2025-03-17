#include "Board.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/King.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Queen.hpp"
#include "pieces/Rook.hpp"
#include "shared/FontManager.hpp"
#include "shared/Notation.hpp"
#include "shared/utils/ColorUtils.hpp"
#include "shared/utils/PositionUtils.hpp"
#include <iostream>

void Board::initializePieces()
{
    createPieces();

    for(auto &row : _board)
    {
        for(auto &piece : row)
        {
            if(piece)
                addChild(piece);
        }
    }

    print();
}

void Board::drawSelf(sf::RenderWindow &window)
{
    window.setView(view.value());

    for(int row = 0; row < GRID_SIZE; row++)
    {
        for(int col = 0; col < GRID_SIZE; col++)
        {
            sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
            cell.setPosition({col * CELL_SIZE, row * CELL_SIZE});

            sf::Color cellColor = getCellColor(row + col);

            if(hoveredCell && hoveredCell == sf::Vector2i{col, row})
                cellColor = ColorUtils::dim(cellColor);

            sf::Vector2i currentCell = sf::Vector2i{col, row};

            if(highlightedMoveCells &&
                   highlightedMoveCells.value().first == currentCell ||
               highlightedMoveCells &&
                   highlightedMoveCells.value().second == currentCell ||
               selectedCell == currentCell)
            {
                cellColor =
                    ColorUtils::blend(cellColor, sf::Color::Yellow, 0.4f);
            }

            cell.setFillColor(cellColor);

            window.draw(cell);
        }
    }

    drawLabels(window);
}

void Board::drawLabels(sf::RenderWindow &window)
{
    const sf::Font &font = FontManager::getFont(FontStyle::Semibold);
    const int fontSize = 12;

    for(int i = 0; i < GRID_SIZE; i++)
    {
        sf::Vector2f filePos((i + 1) * CELL_SIZE - 14,
                             GRID_SIZE * CELL_SIZE - 20);
        sf::Vector2f rankPos(4, (GRID_SIZE - 1 - i) * CELL_SIZE + 2);

        bool isFileOnDark = ((GRID_SIZE - 1) + i) % 2 != 0;
        bool isRankOnDark = ((GRID_SIZE - 1 - i) % 2 != 0);

        sf::Color fileTextColor = isFileOnDark ? colorLight : colorDark;
        sf::Color rankTextColor = isRankOnDark ? colorLight : colorDark;

        sf::Text fileLabel(font, std::string(1, 'a' + i), fontSize);
        fileLabel.setFillColor(fileTextColor);
        fileLabel.setPosition(filePos);
        window.draw(fileLabel);

        sf::Text rankLabel(font, std::to_string(8 - i), fontSize);
        rankLabel.setFillColor(rankTextColor);
        rankLabel.setPosition(rankPos);
        window.draw(rankLabel);
    }
}

EventResult Board::handleSelfEvent(const EventContext &eventCtx)
{
    if(eventCtx.event.is<sf::Event::MouseMoved>())
    {
        const auto mouseMovedEvent =
            eventCtx.event.getIf<sf::Event::MouseMoved>();
        const auto &window = eventCtx.window;
        auto &cursorManager = eventCtx.cursorManager;

        const auto mousePos = mouseMovedEvent->position;
        sf::Vector2f normalizedMousePos =
            PositionUtils::getNormalizedMousePosition(mousePos, window);

        if(!viewportContains(normalizedMousePos))
        {
            cursorManager.resetCursor();
            resetHoveredCell();

            return EventResult::Handled;
        }

        auto cellPosition = getCellFromMousePos(mousePos, window, view.value());

        if(isMouseOverCell(cellPosition))
        {
            if(hoveredCell == cellPosition)
                return EventResult::Consumed;

            cursorManager.setHandCursor();
            hoveredCell = cellPosition;

            std::cout << "Hovered cell: "
                      << Notation::toChessNotation(cellPosition) << "\n";

            return EventResult::Consumed;
        }
    }

    return EventResult::Ignored;
}

void Board::updatePiecePosition(Piece &piece, sf::Vector2i newPosition)
{
    sf::Vector2i piecePosition = piece.getPosition();
    auto p = _board[piecePosition.x][piecePosition.y];
    _board[piecePosition.x][piecePosition.y] = nullptr;
    _board[newPosition.x][newPosition.y] = std::move(p);
    piece.setPosition(newPosition);
}

std::shared_ptr<Piece> Board::getPieceAt(sf::Vector2i cellPosition) const
{
    return _board[cellPosition.x][cellPosition.y];
}

// void Board::createPieces()
// {
//     static constexpr int WHITE_PAWNS_ROW = 2;
//     static constexpr int BLACK_PAWNS_ROW = 7;
//
//     // =============== Pawns =================
//     for(char file = 'A'; file <= 'H'; file++)
//     {
//         pieces.push_back(
//             std::make_shared<Pawn>(Notation::fromChessNotation(std::format(
//                                        "{}{}", file, WHITE_PAWNS_ROW)),
//                                    Side::White));
//         pieces.push_back(
//             std::make_shared<Pawn>(Notation::fromChessNotation(std::format(
//                                        "{}{}", file, BLACK_PAWNS_ROW)),
//                                    Side::Black));
//     }
//
//     // =============== Rooks =================
//     pieces.push_back(
//         std::make_shared<Rook>(Notation::fromChessNotation("A1"),
//         Side::White));
//     pieces.push_back(
//         std::make_shared<Rook>(Notation::fromChessNotation("H1"),
//         Side::White));
//     pieces.push_back(
//         std::make_shared<Rook>(Notation::fromChessNotation("A8"),
//         Side::Black));
//     pieces.push_back(
//         std::make_shared<Rook>(Notation::fromChessNotation("H8"),
//         Side::Black));
//
//     // =============== Knights ===============
//     pieces.push_back(std::make_shared<Knight>(Notation::fromChessNotation("B1"),
//                                               Side::White));
//     pieces.push_back(std::make_shared<Knight>(Notation::fromChessNotation("G1"),
//                                               Side::White));
//     pieces.push_back(std::make_shared<Knight>(Notation::fromChessNotation("B8"),
//                                               Side::Black));
//     pieces.push_back(std::make_shared<Knight>(Notation::fromChessNotation("G8"),
//                                               Side::Black));
//
//     // =============== Bishops ===============
//     pieces.push_back(std::make_shared<Bishop>(Notation::fromChessNotation("C1"),
//                                               Side::White));
//     pieces.push_back(std::make_shared<Bishop>(Notation::fromChessNotation("F1"),
//                                               Side::White));
//     pieces.push_back(std::make_shared<Bishop>(Notation::fromChessNotation("C8"),
//                                               Side::Black));
//     pieces.push_back(std::make_shared<Bishop>(Notation::fromChessNotation("F8"),
//                                               Side::Black));
//
//     // =============== Queens =================
//     pieces.push_back(std::make_shared<Queen>(Notation::fromChessNotation("D1"),
//                                              Side::White));
//     pieces.push_back(std::make_shared<Queen>(Notation::fromChessNotation("D8"),
//                                              Side::Black));
//
//     // =============== Kings ==================
//     pieces.push_back(
//         std::make_shared<King>(Notation::fromChessNotation("E1"),
//         Side::White));
//     pieces.push_back(
//         std::make_shared<King>(Notation::fromChessNotation("E8"),
//         Side::Black));
// }

void Board::createPieces()
{
    static constexpr int WHITE_PAWNS_ROW = 2;
    static constexpr int BLACK_PAWNS_ROW = 7;

    auto placePiece = [&](const std::string &pos, auto piece) {
        auto [row, col] = Notation::fromChessNotation(pos);
        _board[row][col] = std::move(piece);
    };

    // =============== Pawns =================
    for(char file = 'A'; file <= 'H'; file++)
    {
        placePiece(
            std::format("{}{}", file, WHITE_PAWNS_ROW),
            std::make_shared<Pawn>(Notation::fromChessNotation(std::format(
                                       "{}{}", file, WHITE_PAWNS_ROW)),
                                   Side::White));
        placePiece(
            std::format("{}{}", file, BLACK_PAWNS_ROW),
            std::make_shared<Pawn>(Notation::fromChessNotation(std::format(
                                       "{}{}", file, BLACK_PAWNS_ROW)),
                                   Side::Black));
    }

    // =============== Rooks =================
    placePiece("A1", std::make_shared<Rook>(Notation::fromChessNotation("A1"),
                                            Side::White));
    placePiece("H1", std::make_shared<Rook>(Notation::fromChessNotation("H1"),
                                            Side::White));
    placePiece("A8", std::make_shared<Rook>(Notation::fromChessNotation("A8"),
                                            Side::Black));
    placePiece("H8", std::make_shared<Rook>(Notation::fromChessNotation("H8"),
                                            Side::Black));

    // =============== Knights ===============
    placePiece("B1", std::make_shared<Knight>(Notation::fromChessNotation("B1"),
                                              Side::White));
    placePiece("G1", std::make_shared<Knight>(Notation::fromChessNotation("G1"),
                                              Side::White));
    placePiece("B8", std::make_shared<Knight>(Notation::fromChessNotation("B8"),
                                              Side::Black));
    placePiece("G8", std::make_shared<Knight>(Notation::fromChessNotation("G8"),
                                              Side::Black));

    // =============== Bishops ===============
    placePiece("C1", std::make_shared<Bishop>(Notation::fromChessNotation("C1"),
                                              Side::White));
    placePiece("F1", std::make_shared<Bishop>(Notation::fromChessNotation("F1"),
                                              Side::White));
    placePiece("C8", std::make_shared<Bishop>(Notation::fromChessNotation("C8"),
                                              Side::Black));
    placePiece("F8", std::make_shared<Bishop>(Notation::fromChessNotation("F8"),
                                              Side::Black));

    // =============== Queens =================
    placePiece("D1", std::make_shared<Queen>(Notation::fromChessNotation("D1"),
                                             Side::White));
    placePiece("D8", std::make_shared<Queen>(Notation::fromChessNotation("D8"),
                                             Side::Black));

    // =============== Kings ==================
    placePiece("E1", std::make_shared<King>(Notation::fromChessNotation("E1"),
                                            Side::White));
    placePiece("E8", std::make_shared<King>(Notation::fromChessNotation("E8"),
                                            Side::Black));
}

sf::Color Board::getCellColor(int cellPosition) const
{
    return cellPosition % 2 == 0 ? colorLight : colorDark;
};

bool Board::isMouseOverCell(sf::Vector2i mousePos)
{
    int col = mousePos.x / CELL_SIZE;
    int row = mousePos.y / CELL_SIZE;

    return row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE;
}

std::shared_ptr<Piece> Board::getPiece(sf::Vector2i cellPosition) const
{
    return _board[cellPosition.x][cellPosition.y];
}

const sf::View &Board::getView() const { return view.value(); }

sf::Vector2i Board::getCellFromMousePos(const sf::Vector2i &mousePos,
                                        const sf::RenderWindow &window,
                                        const sf::View &view) const
{
    sf::Vector2f localMousePos = window.mapPixelToCoords(mousePos, view);

    return {static_cast<int>(localMousePos.x / CELL_SIZE),
            static_cast<int>(localMousePos.y / CELL_SIZE)};
}

void Board::resetHoveredCell() { hoveredCell = std::nullopt; };

void Board::highlightMove(Move &move)
{
    resetMoveHighlighting();
    highlightedMoveCells = {move.from, move.to};
}

void Board::resetMoveHighlighting() { highlightedMoveCells = std::nullopt; }

void Board::setSelectedCell(sf::Vector2i cellPosition)
{
    selectedCell = cellPosition;
}
void Board::resetSelectedCell() { selectedCell = std::nullopt; }

void Board::print()
{
    for(int col = 0; col < GRID_SIZE; col++)
    {
        for(int row = 0; row < GRID_SIZE; row++)
        {
            auto maybePiece = _board[row][col];
            if(maybePiece != nullptr)
            {
                std::cout << maybePiece->pieceKindToString()[0] << " ";
            }
            else
            {
                std::cout << ". "; // Empty space
            }
        }
        std::cout << "\n";
    }
}
