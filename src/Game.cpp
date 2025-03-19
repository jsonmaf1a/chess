#include "Game.hpp"
#include "managers/SoundManager.hpp"
#include "shared/utils/EventUtils.hpp"
#include "shared/utils/PositionUtils.hpp"
#include <iostream>

EventResult Game::handleEvent(const EventContext &eventCtx)
{
    if(EventUtils::isLeftClickEvent(eventCtx.event))
    {
        auto mouseClickEvent =
            eventCtx.event.getIf<sf::Event::MouseButtonPressed>();
        const auto &window = eventCtx.window;

        const auto mousePos = mouseClickEvent->position;
        sf::Vector2f normalizedMousePos =
            PositionUtils::getNormalizedMousePosition(mousePos, window);

        if(!board->viewportContains(normalizedMousePos))
            return EventResult::Handled;

        auto cellPosition =
            board->getCellFromMousePos(mousePos, window, board->getView());

        std::shared_ptr<Piece> maybePiece = board->getPiece(cellPosition);

        if(maybePiece && maybePiece->getSide() == currentSide)
        {
            handlePieceSelection(cellPosition, maybePiece);
            return EventResult::Consumed;
        }

        if(selectedPiece.has_value())
        {
            move(selectedPiece->get(), cellPosition);
            return EventResult::Consumed;
        }

        std::cout << "nothing\n";
        selectedPiece = std::nullopt;
        printGameState();
        return EventResult::Consumed;
    }

    return EventResult::Ignored;
}

void Game::handlePieceSelection(const sf::Vector2i &cellPosition,
                                const std::shared_ptr<Piece> piece)
{
    selectedPiece = *piece;
    board->setSelectedCell(cellPosition);

    auto legalMoves =
        selectedPiece->get().getLegalMoves(board->getPiecesOnBoard());
    board->setPossibleMoves(legalMoves);

    printGameState();
}

void Game::move(Piece &piece, sf::Vector2i newPosition)
{
    if(!piece.isLegalMove(board->getPiecesOnBoard(), newPosition))
    {
        selectedPiece = std::nullopt;
        board->resetSelectedCell();
        board->resetPossibleMoves();
        SoundManager::playSound(SoundKind::IllegalMove);
        return;
    }

    if(!piece.wasMoved)
        piece.wasMoved = true;

    moves.push_back(std::make_unique<Move>(
        piece, static_cast<sf::Vector2i>(piece.getPosition()), newPosition));

    board->setLastMoveCells(*moves.back());
    board->updatePiecePosition(piece, newPosition);
    SoundManager::playSound(SoundKind::MoveSelf);

    selectedPiece = std::nullopt;
    board->resetPossibleMoves();
    nextTurn();

    printGameState();
}

void Game::nextTurn()
{
    currentSide = currentSide == Side::White ? Side::Black : Side::White;
}

void Game::printGameState()
{
    std::cout << "BOARD:" << "\n";
    board->printSelf();
    std::cout << "\n\n";

    std::cout << "SELECTED PIECE: ";
    if(selectedPiece.has_value())
        selectedPiece.value().get().printSelf();
    std::cout << "\n";
}
