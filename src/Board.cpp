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

    sf::RectangleShape rect(sf::Vector2f(CELL_SIZE, CELL_SIZE));
    rect.setPosition({position.x * CELL_SIZE, position.y * CELL_SIZE});
    rect.setFillColor(color);

    window.draw(rect);
}

void Board::drawPossibleMove(sf::RenderWindow &window,
                             const sf::Vector2i &position)
{
    constexpr float radius = 15.f;

    sf::CircleShape circle(radius);
    circle.setPosition(
        {position.x * Board::CELL_SIZE + Board::CELL_SIZE / 2.f - radius,
         position.y * Board::CELL_SIZE + Board::CELL_SIZE / 2.f - radius});

    sf::Color color = sf::Color::Black;
    color.a = 30;
    circle.setFillColor(color);

    window.draw(circle);
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
            auto &piece = _board[i][j];
            if(piece != nullptr)
            {
                filtered.push_back(piece);
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

    // =============== Pawns =================
    for(char file = 'A'; file <= 'H'; file++)
    {
        placePiece<Pawn>(file + WHITE_PAWNS_ROW, Side::White);
        placePiece<Pawn>(file + BLACK_PAWNS_ROW, Side::Black);
    }

    // =============== Rooks =================
    placePiece<Rook>("A1", Side::White);
    placePiece<Rook>("H1", Side::White);
    placePiece<Rook>("A8", Side::Black);
    placePiece<Rook>("H8", Side::Black);

    // =============== Knights ===============
    placePiece<Knight>("B1", Side::White);
    placePiece<Knight>("G1", Side::White);
    placePiece<Knight>("B8", Side::Black);
    placePiece<Knight>("G8", Side::Black);

    // =============== Bishops ===============
    placePiece<Bishop>("C1", Side::White);
    placePiece<Bishop>("F1", Side::White);
    placePiece<Bishop>("C8", Side::Black);
    placePiece<Bishop>("F8", Side::Black);

    // =============== Queens =================
    placePiece<Queen>("D1", Side::White);
    placePiece<Queen>("D8", Side::Black);

    // =============== Kings ==================
    placePiece<King>("E1", Side::White);
    placePiece<King>("E8", Side::Black);
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

void Board::setPossibleMoves(const std::vector<sf::Vector2i> &possibleMoves)
{

    this->possibleMoves = possibleMoves;
}

void Board::resetSelectedCell() { selectedCell = std::nullopt; }
void Board::resetHoveredCell() { hoveredCell = std::nullopt; }
void Board::resetLastMoveCells() { lastMoveCells = std::nullopt; }
void Board::resetPossibleMoves() { possibleMoves.clear(); }
