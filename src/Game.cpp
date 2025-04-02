#include "Game.hpp"
#include "managers/SoundManager.hpp"
#include "shared/utils/EventUtils.hpp"
#include "shared/utils/PositionUtils.hpp"
#include <chrono>
#include <iostream>

void Game::update()
{
    if(!state.hasGameStarted)
    {
        clock.restart();
        return;
    }

    if(state.hasGameStarted && state.isPlaying)
    {
        auto dt = std::chrono::milliseconds(clock.restart().asMilliseconds());
        state.decrementTimeForCurrentSide(dt);
    }
}

EventResult Game::handleEvent(const EventContext &eventCtx)
{
    if(!state.isPlaying)
        return EventResult::Handled;

    if(EventUtils::isLeftClickEvent(eventCtx.event))
    {
        auto mouseClickEvent =
            eventCtx.event.getIf<sf::Event::MouseButtonPressed>();
        const auto &window = eventCtx.window;

        const auto mousePos = mouseClickEvent->position;
        sf::Vector2f normalizedMousePos =
            PositionUtils::normalizePosition(mousePos, window);

        if(!board->viewportContains(normalizedMousePos))
            return EventResult::Handled;

        auto cellPosition = board->getCellFromMousePos(window, mousePos);

        auto maybePiece = board->getPiece(cellPosition);

        if(maybePiece && maybePiece->getSide() == state.currentSide)
        {
            handleSelectPiece(maybePiece, cellPosition);
            return EventResult::Handled;
        }

        if(state.selectedPiece)
        {
            handleMovePiece(state.selectedPiece, cellPosition);
            return EventResult::Handled;
        }

        std::cout << "nothing\n";
        if(state.selectedPiece)
            state.selectedPiece.reset();
        printInfo();

        return EventResult::Handled;
    }

    return EventResult::Ignored;
}

void Game::handleSelectPiece(std::shared_ptr<Piece> piece,
                             const sf::Vector2i cellPosition)
{
    state.selectedPiece = std::move(piece);
    board->setSelectedCell(cellPosition);

    auto validMoves = board->getValidMoves(*state.selectedPiece);
    board->setPossibleMoves(validMoves);
    printInfo();
}

void Game::handleMovePiece(std::shared_ptr<Piece> piece,
                           sf::Vector2i toPosition)
{
    if(!board->isValidMove(*piece, toPosition))
        return handleIllegalMove();

    if(!piece->hasMoved)
        piece->hasMoved = true;

    sf::Vector2i prevPosition = piece->getPosition();

    auto capturedPieceKind = handleCapture(piece, toPosition);

    board->updatePiecePosition(*piece, toPosition);

    state.addMove(std::make_unique<Move>(*piece, prevPosition, toPosition,
                                         capturedPieceKind));
    board->setLastMoveCells(*state.moves.back());

    SoundManager::playSound(capturedPieceKind
                                ? SoundKind::Capture
                                : (state.currentSide == Side::White
                                       ? SoundKind::MoveSelf
                                       : SoundKind::MoveOpponent));

    handleNextTurn();
    printInfo();
}

std::optional<PieceKind> Game::handleCapture(std::shared_ptr<Piece> piece,
                                             sf::Vector2i position)
{
    auto pieceToCapture = board->getPiece(position);
    if(!pieceToCapture)
        return std::nullopt;

    PieceKind kind = pieceToCapture->getKind();
    board->removeChild(pieceToCapture);

    return kind;
}

void Game::handleCastling(std::shared_ptr<Piece> piece, sf::Vector2i toPosition)
{
    // auto pos1 = state.selectedPiece->get().getPosition();
    // auto pos2 = toPosition;
    //
    // auto piece1 = board->getPiece(pos1);
    // auto piece2 = board->getPiece(pos2);
    //
    // if(!piece1 || !piece2)
    //     return;
    //
    // sf::Vector2i pos1Current = piece1->getPosition();
    // sf::Vector2i pos2Current = piece2->getPosition();
    //
    // piece1->updatePositionWithTransition(pos2Current);
    // piece2->updatePositionWithTransition(pos1Current);
    //
    // _board[pos1.x][pos1.y] = std::move(piece2);
    // _board[pos2.x][pos2.y] = std::move(piece1);

    piece->hasMoved = true;

    state.addMove(std::make_unique<Move>(
        *piece, static_cast<sf::Vector2i>(piece->getPosition()), toPosition));

    SoundManager::playSound(SoundKind::Castle);
    handleNextTurn();
}

void Game::handleNextTurn()
{
    board->resetPossibleMoves();
    state.incrementTimeForCurrentSide();
    state.selectedPiece.reset();
    state.nextSide();
}

void Game::handleIllegalMove()
{
    state.selectedPiece.reset();
    board->resetSelectedCell();
    board->resetPossibleMoves();
    SoundManager::playSound(SoundKind::IllegalMove);
}

bool Game::isCastling(Piece &piece, sf::Vector2i toPosition)
{
    auto maybeRook = board->getPiece(toPosition);

    if(!maybeRook || maybeRook->getKind() != PieceKind::Rook ||
       maybeRook->hasMoved)
        return false;

    if(piece.getKind() != PieceKind::King || piece.hasMoved)
        return false;

    return true;
}

GameState &Game::getState() { return state; }

void Game::printInfo()
{
    board->printSelf();
    state.print();
}
