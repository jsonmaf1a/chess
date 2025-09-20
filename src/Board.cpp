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

    printSelf();
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

    for(const auto &[pos, isCapture] : possibleMoves)
    {
        drawPossibleMove(window, pos, isCapture);
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
                             const sf::Vector2i position, const bool isCapture)
{
    const int alpha = 30;
    sf::Color color = sf::Color(0, 0, 0, alpha);

    std::unique_ptr<sf::Drawable> moveIndicator;

    if(!isCapture)
    {
        const float radius = 15.f;

        auto circle = std::make_unique<sf::CircleShape>(radius, 256);
        circle->setFillColor(color);

        circle->setOrigin({radius, radius});

        moveIndicator = std::move(circle);
    }
    else
    {
        const int offset = 2.f;
        const float outer = BoardConfig::CellSize / 2.f - offset;
        const float inner = outer - 10.f;

        auto ring = std::make_unique<VertexShapes::Ring>(inner, outer);
        ring->setFillColor(color);

        moveIndicator = std::move(ring);
    }

    if(auto *transformable =
           dynamic_cast<sf::Transformable *>(moveIndicator.get()))
    {
        transformable->setPosition(
            {position.x * BoardConfig::CellSize + BoardConfig::CellSize / 2.f,
             position.y * BoardConfig::CellSize + BoardConfig::CellSize / 2.f});
    }

    window.draw(*moveIndicator);
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

        auto cellPosition = sf::Vector2i(getCellFromMousePos(window, mousePos));

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

void Board::updatePiecePosition(Piece &piece, sf::Vector2i newPosition)
{
    sf::Vector2i piecePosition = sf::Vector2i{piece.getPosition()};

    auto _piece = _board[piecePosition.x][piecePosition.y];
    _board[piecePosition.x][piecePosition.y] = nullptr;
    _board[newPosition.x][newPosition.y] = std::move(_piece);

    piece.updatePositionWithTransition(newPosition);
}

std::vector<std::pair<sf::Vector2i, bool>> Board::getValidMoves(
    Piece &piece) const
{
    std::vector<std::pair<sf::Vector2i, bool>> validMoves;
    // std::vector<sf::Vector2i> legalMoves = piece.getLegalMoves();
    //
    // for(const auto &move : legalMoves)
    // {
    //     if(move.x < 0 || move.x >= BoardConfig::GridSize || move.y < 0 ||
    //        move.y >= BoardConfig::GridSize)
    //         continue;
    //
    //     std::shared_ptr<Piece> targetPiece = getPiece(move);
    //
    //     if(piece.getKind() == PieceKind::Pawn)
    //     {
    //         // Forward moves must be empty
    //         if(move.x == piece.getPosition().x)
    //         {
    //             if(!targetPiece)
    //                 validMoves.push_back({move, false});
    //         }
    //         // Diagonal moves must be captures
    //         else if(targetPiece && targetPiece->getSide() != piece.getSide())
    //         {
    //             validMoves.push_back({move, true});
    //         }
    //         continue;
    //     }
    //
    //     // Standard logic for non-pawn pieces
    //     if(!targetPiece)
    //     {
    //         validMoves.push_back({move, false});
    //     }
    //     else if(targetPiece->getSide() != piece.getSide())
    //     {
    //         validMoves.push_back({move, true});
    //     }
    // }
    //
    return validMoves;
}
bool Board::isValidMove(Piece &piece, sf::Vector2i newPosition) const
{
    auto moves = getValidMoves(piece);
    // auto it = std::find(moves.begin(), moves.end(), newPosition);

    auto it = std::find_if(moves.begin(), moves.end(),
                           [&](std::pair<sf::Vector2i, bool> item) {
                               return item.first == newPosition;
                           });

    return it != moves.end();
};

template <typename T>
    requires std::is_base_of<Piece, T>::value
void Board::placePiece(const std::string &pos, Side side)
{
    auto position = Notation::fromChessNotation(pos);
    std::shared_ptr<Piece> piece = std::make_shared<T>(side, position);
    _board[position.x][position.y] = std::move(piece);
}

void Board::createPieces()
{
    const std::string WHITE_PAWNS_ROW = "2";
    const std::string BLACK_PAWNS_ROW = "7";

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

sf::Vector2i Board::getCellFromMousePos(const sf::RenderWindow &window,
                                        const sf::Vector2i mousePos) const
{
    sf::Vector2f localMousePos =
        window.mapPixelToCoords(mousePos, getView().value());

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

void Board::setPossibleMoves(
    const std::vector<std::pair<sf::Vector2i, bool>> possibleMoves)
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
                std::cout << StringUtils::toChar(maybePiece->getKind());
            else
                std::cout << ".";
            std::cout << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\n";
}
