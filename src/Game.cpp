#include "Game.hpp"
#include "managers/SoundManager.hpp"
#include "shared/utils/EventUtils.hpp"
#include "shared/utils/PositionUtils.hpp"
#include <iostream>

void Game::start() { state.isStarted = true; }

void Game::update() {}

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
        printGameState();
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

    printGameState();
}

void Game::move(Piece &piece, sf::Vector2i newPosition)
{
    if(!piece.isLegalMove(newPosition))
    {
        state.selectedPiece = std::nullopt;
        board->resetSelectedCell();
        board->resetPossibleMoves();
        SoundManager::playSound(SoundKind::IllegalMove);
        return;
    }

    if(!piece.wasMoved)
        piece.wasMoved = true;

    state.moves.push_back(std::make_unique<Move>(
        piece, static_cast<sf::Vector2i>(piece.getPosition()), newPosition));

    board->setLastMoveCells(*state.moves.back());
    board->updatePiecePosition(piece, newPosition);
    SoundManager::playSound(SoundKind::MoveSelf);

    state.selectedPiece = std::nullopt;
    board->resetPossibleMoves();
    nextTurn();

    printGameState();
}

void Game::nextTurn()
{
    state.currentSide =
        state.currentSide == Side::White ? Side::Black : Side::White;
}

GameState &Game::getState() { return state; }

void Game::printGameState()
{
    std::cout << "BOARD:" << "\n";
    board->printSelf();
    std::cout << "\n\n";

    std::cout << "SELECTED PIECE: ";
    if(state.selectedPiece.has_value())
        state.selectedPiece.value().get().printSelf();
    std::cout << "\n";
}
