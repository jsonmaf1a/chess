#include "Board.hpp"
#include "managers/FontManager.hpp"
#include "managers/ThemeManager.hpp"
#include "pieces/Bishop.hpp"
#include "pieces/King.hpp"
#include "pieces/Knight.hpp"
#include "pieces/Pawn.hpp"
#include "pieces/Queen.hpp"
#include "pieces/Rook.hpp"
#include "shared/Notation.hpp"
#include "shared/VertexShapes.hpp"
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

#ifdef DEBUG
    printSelf();
#endif // DEBUG
}

void Board::drawSelf(sf::RenderWindow &window)
{
    window.setView(view.value());

    for(int row = 0; row < BoardConfig::GridSize; row++)
    {
        for(int col = 0; col < BoardConfig::GridSize; col++)
        {
            drawCell(window, {col, row});
        }
    }

    for(const auto &pos : possibleMoves)
    {
        drawPossibleMove(window, pos);
    }

    drawLabels(window);
    drawHighlights(window);
}

void Board::drawCell(sf::RenderWindow &window, sf::Vector2i position,
                     sf::Color color)
{
    if(color == sf::Color::Transparent)
        color = getCellColor(position.x + position.y);

    sf::RectangleShape rect(
        sf::Vector2f(BoardConfig::CellSize, BoardConfig::CellSize));
    rect.setPosition({position.x * BoardConfig::CellSize,
                      position.y * BoardConfig::CellSize});
    rect.setFillColor(color);

    window.draw(rect);
}

void Board::drawPossibleMove(sf::RenderWindow &window,
                             const sf::Vector2i position)
{
    const int alpha = 30;
    sf::Color color = sf::Color(0, 0, 0, alpha);

    if(!getPiece(position))
    {
        const float radius = 15.f;
        sf::CircleShape circle(radius);
        circle.setFillColor(color);
        circle.setPosition({position.x * BoardConfig::CellSize +
                                BoardConfig::CellSize / 2.f - radius,
                            position.y * BoardConfig::CellSize +
                                BoardConfig::CellSize / 2.f - radius});
        window.draw(circle);
    }
    else
    {
        const int offset = 5.f;
        const float outer = BoardConfig::CellSize / 2.f - offset;
        const float inner = outer - 10.f;
        VertexShapes::Ring ring(inner, outer);
        ring.setFillColor(color);
        ring.setPosition(
            {position.x * BoardConfig::CellSize + BoardConfig::CellSize / 2.f,
             position.y * BoardConfig::CellSize + BoardConfig::CellSize / 2.f});
        window.draw(ring);
    }
}

void Board::drawHighlights(sf::RenderWindow &window)
{
    Theme theme = ThemeManager::getTheme();

    if(hoveredCell)
    {
        sf::Color color = theme.board.hovered;

        drawCell(window, hoveredCell.value(), color);
    }

    if(selectedCell)
    {
        sf::Color color = theme.board.selected;

        drawCell(window, selectedCell.value(), color);
    }

    if(lastMoveCells)
    {
        sf::Color color = theme.board.highlighted;

        drawCell(window, lastMoveCells.value().first, color);
        drawCell(window, lastMoveCells.value().second, color);
    }
}

void Board::drawLabels(sf::RenderWindow &window)
{
    Theme theme = ThemeManager::getTheme();
    const sf::Font &font = FontManager::getFont(FontStyle::Semibold);
    const int fontSize = 12;

    for(int i = 0; i < BoardConfig::GridSize; i++)
    {
        sf::Vector2f filePos((i + 1) * BoardConfig::CellSize - 14,
                             BoardConfig::GridSize * BoardConfig::CellSize -
                                 20);
        sf::Vector2f rankPos(
            4, (BoardConfig::GridSize - 1 - i) * BoardConfig::CellSize + 2);

        bool isFileOnDark = ((BoardConfig::GridSize - 1) + i) % 2 != 0;
        bool isRankOnDark = ((BoardConfig::GridSize - 1 - i) % 2 != 0);

        sf::Color fileTextColor =
            isFileOnDark ? theme.board.light : theme.board.dark;
        sf::Color rankTextColor =
            isRankOnDark ? theme.board.light : theme.board.dark;

        sf::Text fileLabel(font, std::string(1, 'a' + i), fontSize);
        fileLabel.setFillColor(fileTextColor);
        fileLabel.setPosition(filePos);
        window.draw(fileLabel);

        sf::Text rankLabel(font, std::to_string(1 + i), fontSize);
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
            PositionUtils::normalizePosition(mousePos, window);

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
                return EventResult::Handled;

            cursorManager.setHandCursor();
            setHoveredCell(cellPosition);

            std::cout << "Hovered cell: "
                      << Notation::toChessNotation(cellPosition) << "\n";

            return EventResult::Handled;
        }
    }

    return EventResult::Ignored;
}

std::vector<std::shared_ptr<Piece>> Board::getPiecesOnBoard()
{
    std::vector<std::shared_ptr<Piece>> filtered;

    for(int i = 0; i < BoardConfig::GridSize; ++i)
    {
        for(int j = 0; j < BoardConfig::GridSize; ++j)
        {
            auto &piece = _board[i][j];
            if(piece != nullptr)
            {
                filtered.push_back(piece);
            }
        }
    }

    return filtered;
}

void Board::updatePiecePosition(Piece &piece, sf::Vector2i newPosition)
{
    sf::Vector2i piecePosition = sf::Vector2i{piece.getPosition()};

    auto _piece = _board[piecePosition.x][piecePosition.y];
    _board[piecePosition.x][piecePosition.y] = nullptr;
    _board[newPosition.x][newPosition.y] = std::move(_piece);

    piece.updatePositionWithTransition(newPosition);
}

void Board::swapPieces(sf::Vector2i pos1, sf::Vector2i pos2)
{
    auto piece1 = getPiece(pos1);
    auto piece2 = getPiece(pos2);

    if(!piece1 || !piece2)
        return;

    sf::Vector2i pos1Current = piece1->getPosition();
    sf::Vector2i pos2Current = piece2->getPosition();

    piece1->updatePositionWithTransition(pos2Current);
    piece2->updatePositionWithTransition(pos1Current);

    _board[pos1.x][pos1.y] = std::move(piece2);
    _board[pos2.x][pos2.y] = std::move(piece1);
}

template <typename T>
    requires std::is_base_of<Piece, T>::value
void Board::placePiece(const std::string &pos, Side side)
{
    auto [row, col] = Notation::fromChessNotation(pos);

    std::shared_ptr<Piece> piece = std::make_shared<T>(side);
    piece->setPosition({row, col});

    _board[row][col] = std::move(piece);
}

void Board::createPieces()
{
    static constexpr std::string WHITE_PAWNS_ROW = "2";
    static constexpr std::string BLACK_PAWNS_ROW = "7";

    for(char file = 'A'; file <= 'H'; file++)
    {
        placePiece<Pawn>(file + WHITE_PAWNS_ROW, Side::White);
        placePiece<Pawn>(file + BLACK_PAWNS_ROW, Side::Black);
    }

    placePiece<Rook>("A1", Side::White);
    placePiece<Rook>("H1", Side::White);
    placePiece<Rook>("A8", Side::Black);
    placePiece<Rook>("H8", Side::Black);

    placePiece<Knight>("B1", Side::White);
    placePiece<Knight>("G1", Side::White);
    placePiece<Knight>("B8", Side::Black);
    placePiece<Knight>("G8", Side::Black);

    placePiece<Bishop>("C1", Side::White);
    placePiece<Bishop>("F1", Side::White);
    placePiece<Bishop>("C8", Side::Black);
    placePiece<Bishop>("F8", Side::Black);

    placePiece<Queen>("D1", Side::White);
    placePiece<Queen>("D8", Side::Black);

    placePiece<King>("E1", Side::White);
    placePiece<King>("E8", Side::Black);
}

sf::Color Board::getCellColor(int cellPosition) const
{
    Theme theme = ThemeManager::getTheme();
    return cellPosition % 2 == 0 ? theme.board.light : theme.board.dark;
};

bool Board::isMouseOverCell(sf::Vector2i mousePos)
{
    int col = mousePos.x / BoardConfig::CellSize;
    int row = mousePos.y / BoardConfig::CellSize;

    return row >= 0 && row < BoardConfig::GridSize && col >= 0 &&
           col < BoardConfig::GridSize;
}

std::shared_ptr<Piece> Board::getPiece(sf::Vector2i cellPosition) const
{
    return _board[cellPosition.x][cellPosition.y];
}

const sf::View &Board::getView() const { return view.value(); }

sf::Vector2i Board::getCellFromMousePos(const sf::Vector2i mousePos,
                                        const sf::RenderWindow &window,
                                        const sf::View &view) const
{
    sf::Vector2f localMousePos = window.mapPixelToCoords(mousePos, view);

    return sf::Vector2i(localMousePos.x / BoardConfig::CellSize,
                        localMousePos.y / BoardConfig::CellSize);
}

void Board::setSelectedCell(const sf::Vector2i cellPosition)
{
    selectedCell = cellPosition;
}
void Board::setHoveredCell(const sf::Vector2i cellPosition)
{
    hoveredCell = cellPosition;
}
void Board::setLastMoveCells(const Move move)
{
    lastMoveCells = std::make_pair(move.from, move.to);
}

void Board::setPossibleMoves(const std::vector<sf::Vector2i> possibleMoves)
{

    this->possibleMoves = possibleMoves;
}

void Board::resetSelectedCell() { selectedCell = std::nullopt; }
void Board::resetHoveredCell() { hoveredCell = std::nullopt; }
void Board::resetLastMoveCells() { lastMoveCells = std::nullopt; }
void Board::resetPossibleMoves() { possibleMoves.clear(); }

void Board::printSelf() const
{
    for(int col = 0; col < BoardConfig::GridSize; col++)
    {
        for(int row = 0; row < BoardConfig::GridSize; row++)
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
