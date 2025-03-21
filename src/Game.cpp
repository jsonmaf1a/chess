#include "Game.hpp"
#include "managers/SoundManager.hpp"
#include "shared/utils/EventUtils.hpp"
#include "shared/utils/PositionUtils.hpp"
#include <iostream>

void Game::update()
{
    if(!state.isPlaying)
    {
        clock.restart();
        return;
    }

    if(state.moves.size() != 0)
    {
        unsigned int dt = clock.restart().asMilliseconds();
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

        auto cellPosition =
            board->getCellFromMousePos(mousePos, window, board->getView());

        std::shared_ptr<Piece> maybePiece = board->getPiece(cellPosition);

        if(maybePiece && maybePiece->getSide() == state.currentSide)
        {
            if(isCastling(state.selectedPiece->get(), cellPosition))
            {
                handleCastling(state.selectedPiece->get(), cellPosition);
                return EventResult::Handled;
            }

            handlePieceSelection(cellPosition, maybePiece);
            return EventResult::Handled;
        }

        if(state.selectedPiece.has_value())
        {
            handlePieceMove(state.selectedPiece->get(), cellPosition);
            return EventResult::Handled;
        }

        std::cout << "nothing\n";
        state.selectedPiece = std::nullopt;
        printInfo();

        return EventResult::Handled;
    }

    return EventResult::Ignored;
}

void Game::handlePieceSelection(const sf::Vector2i cellPosition,
                                const std::shared_ptr<Piece> piece)
{
    state.selectedPiece = *piece;
    board->setSelectedCell(cellPosition);

    auto legalMoves = state.selectedPiece->get().getLegalMoves();
    board->setPossibleMoves(legalMoves);

    printInfo();
}

void Game::handlePieceMove(Piece &piece, sf::Vector2i toPosition)
{
    if(!piece.isLegalMove(toPosition))
        return handleIllegalMove();

    if(!piece.wasMoved)
        piece.wasMoved = true;

    movePiece(piece, toPosition);
    handleNextTurn();
    printInfo();
}

void Game::movePiece(Piece &piece, sf::Vector2i toPosition)
{
    auto capturedPieceKind = handleCapturing(piece, toPosition);

    board->updatePiecePosition(piece, toPosition);

    state.moves.push_back(std::make_unique<Move>(
        piece, piece.getPosition(), toPosition, capturedPieceKind));
    board->setLastMoveCells(*state.moves.back());

    SoundManager::playSound(capturedPieceKind
                                ? SoundKind::Capture
                                : (state.currentSide == Side::White
                                       ? SoundKind::MoveSelf
                                       : SoundKind::MoveOpponent));
}

std::optional<PieceKind> Game::handleCapturing(Piece &piece,
                                               sf::Vector2i position)
{
    auto pieceToCapture = board->getPiece(position);
    if(!pieceToCapture)
        return std::nullopt;

    board->removeChild(pieceToCapture);

    return pieceToCapture->getKind();
}

void Game::handleCastling(Piece &piece, sf::Vector2i toPosition)
{
    board->swapPieces(state.selectedPiece->get().getPosition(), toPosition);
    piece.wasMoved = true;

    state.moves.push_back(std::make_unique<Move>(
        piece, static_cast<sf::Vector2i>(piece.getPosition()), toPosition));

    SoundManager::playSound(SoundKind::Castle);
    handleNextTurn();
}

void Game::handleNextTurn()
{
    board->resetPossibleMoves();
    state.incrementTimeForCurrentSide();
    state.selectedPiece = std::nullopt;
    state.nextSide();
}

void Game::handleIllegalMove()
{
    state.selectedPiece = std::nullopt;
    board->resetSelectedCell();
    board->resetPossibleMoves();
    SoundManager::playSound(SoundKind::IllegalMove);
}

bool Game::isCastling(Piece &piece, sf::Vector2i toPosition)
{
    auto maybeRook = board->getPiece(toPosition);

    if(!maybeRook || maybeRook->getKind() != PieceKind::Rook ||
       maybeRook->wasMoved)
        return false;

    if(piece.getKind() != PieceKind::King || piece.wasMoved)
        return false;

    return true;
}

GameState &Game::getState() { return state; }

void Game::printInfo()
{
    board->printSelf();
    state.print();
}
