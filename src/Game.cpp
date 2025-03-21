#define DEBUG

#include "Game.hpp"
#include "managers/SoundManager.hpp"
#include "shared/utils/EventUtils.hpp"
#include "shared/utils/PositionUtils.hpp"
#include <iostream>

void Game::update()
{
    if(!state.isStarted)
    {
        clock.restart();
        return;
    }

    unsigned int dt = clock.restart().asMilliseconds();
    state.decrementTimeForCurrentSide(dt);
}

EventResult Game::handleEvent(const EventContext &eventCtx)
{
    if(!state.isStarted)
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
            handlePieceSelection(cellPosition, maybePiece);
            return EventResult::Handled;
        }

        if(state.selectedPiece.has_value())
        {
            move(state.selectedPiece->get(), cellPosition);
            return EventResult::Handled;
        }

        std::cout << "nothing\n";
        state.selectedPiece = std::nullopt;

#ifdef DEBUG
        board->printSelf();
        state.print();
#endif

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

#ifdef DEBUG
    board->printSelf();
    state.print();
#endif
}

void Game::move(Piece &piece, sf::Vector2i newPosition)
{
    if(!piece.isLegalMove(newPosition))
        return handleIllegalMove();

    if(!piece.wasMoved)
        piece.wasMoved = true;

    bool isCapturing = false;
    std::optional<PieceKind> capturedPieceKind;
    auto pieceToCapture = board->getPiece(newPosition);
    if(pieceToCapture)
    {
        isCapturing = true;
        board->removeChild(pieceToCapture);
        capturedPieceKind = pieceToCapture->getKind();
    }

    state.moves.push_back(std::make_unique<Move>(
        piece, static_cast<sf::Vector2i>(piece.getPosition()), newPosition,
        capturedPieceKind));

    board->setLastMoveCells(*state.moves.back());
    board->updatePiecePosition(piece, newPosition);

    SoundManager::playSound(isCapturing ? SoundKind::Capture
                                        : SoundKind::MoveSelf);

    state.incrementTimeForCurrentSide();
    state.selectedPiece = std::nullopt;
    board->resetPossibleMoves();
    state.nextTurn();

#ifdef DEBUG
    board->printSelf();
    state.print();
#endif
}

void Game::handleIllegalMove()
{
    state.selectedPiece = std::nullopt;
    board->resetSelectedCell();
    board->resetPossibleMoves();
    SoundManager::playSound(SoundKind::IllegalMove);
}

GameState &Game::getState() { return state; }
