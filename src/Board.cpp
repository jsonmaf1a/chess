#include "Board.hpp"
#include "managers/FontManager.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/King.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Queen.hpp"
#include "pieces/Rook.hpp"
#include "shared/Notation.hpp"
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

    printSelf();
}

void Board::drawSelf(sf::RenderWindow &window)
{
    window.setView(view.value());

    for(int row = 0; row < GRID_SIZE; row++)
    {
        for(int col = 0; col < GRID_SIZE; col++)
        {
            drawCell(window, {col, row});
        }
    }

    drawLabels(window);
    drawHighlights(window);
}

void Board::drawCell(sf::RenderWindow &window, sf::Vector2i position,
                     sf::Color color)
{
    if(color == sf::Color::Transparent)
        color = getCellColor(position.x + position.y);

    sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    rect.setPosition({position.x * CELL_SIZE, position.y * CELL_SIZE});
    rect.setFillColor(color);

    window.draw(rect);
}

void Board::drawHighlights(sf::RenderWindow &window)
{
    constexpr int HIGHLIGHT_OPACITY = 60;

    auto createHighlightColor = [](sf::Color color,
                                   int alpha = HIGHLIGHT_OPACITY) {
        color.a = alpha;
        return color;
    };

    if(hoveredCell)
    {
        sf::Color color = sf::Color::Black;

        drawCell(window, hoveredCell.value(), createHighlightColor(color, 10));
    }

    if(selectedCell)
    {
        drawCell(window, selectedCell.value(),
                 createHighlightColor(sf::Color::Yellow));
    }

    if(lastMoveCells)
    {
        sf::Color highlightColor = createHighlightColor(sf::Color::Yellow);
        drawCell(window, lastMoveCells.value().first, highlightColor);
        drawCell(window, lastMoveCells.value().second, highlightColor);
    }
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

        auto cellPosition =
            sf::Vector2i(getCellFromMousePos(mousePos, window, view.value()));

        if(isMouseOverCell(cellPosition))
        {
            if(hoveredCell == cellPosition)
                return EventResult::Consumed;

            cursorManager.setHandCursor();
            setHoveredCell(cellPosition);

            std::cout << "Hovered cell: "
                      << Notation::toChessNotation(cellPosition) << "\n";

            return EventResult::Consumed;
        }
    }

    return EventResult::Ignored;
}

std::vector<std::shared_ptr<Piece>> Board::getPiecesOnBoard()
{
    std::vector<std::shared_ptr<Piece>> filtered;

    for(int i = 0; i < GRID_SIZE; ++i)
    {
        for(int j = 0; j < GRID_SIZE; ++j)
        {
            if(_board[i][j] != nullptr)
            {
                filtered.push_back(_board[i][j]);
            }
        }
    }

    return filtered;
}

void Board::updatePiecePosition(Piece &piece, sf::Vector2i &newPosition)
{
    sf::Vector2i piecePosition = sf::Vector2i{piece.getPosition()};

    auto _piece = _board[piecePosition.x][piecePosition.y];
    _board[piecePosition.x][piecePosition.y] = nullptr;
    _board[newPosition.x][newPosition.y] = std::move(_piece);

    piece.updatePositionWithTransition(sf::Vector2f{newPosition});
}

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

    return sf::Vector2i(localMousePos.x / CELL_SIZE,
                        localMousePos.y / CELL_SIZE);
}

void Board::printSelf() const
{
    for(int col = 0; col < GRID_SIZE; col++)
    {
        for(int row = 0; row < GRID_SIZE; row++)
        {
            auto maybePiece = _board[row][col];
            if(maybePiece)
            {
                std::cout << (maybePiece->getKind() == PieceKind::Knight
                                  ? 'n'
                                  : maybePiece->getStringifiedKind()[0]);
            }
            else
            {
                std::cout << ".";
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n";
}

void Board::setSelectedCell(const sf::Vector2i &cellPosition)
{
    selectedCell = cellPosition;
}
void Board::setHoveredCell(const sf::Vector2i &cellPosition)
{
    hoveredCell = cellPosition;
}
void Board::setLastMoveCells(const Move &move)
{
    lastMoveCells = std::make_pair(move.from, move.to);
}

void Board::resetSelectedCell() { selectedCell = std::nullopt; }
void Board::resetHoveredCell() { hoveredCell = std::nullopt; }
void Board::resetLastMoveCells() { lastMoveCells = std::nullopt; }
