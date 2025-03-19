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
    selectedPiece->get().printLegalMoves(board->getPiecesOnBoard());

    printGameState();
}

void Game::move(Piece &piece, sf::Vector2i newPosition)
{
    std::cout << "\nok\n\n";
    if(!piece.isLegalMove(board->getPiecesOnBoard(), newPosition))
    {
        SoundManager::playSound(SoundKind::IllegalMove);
        selectedPiece = std::nullopt;
        return;
    }

    if(!piece.wasMoved)
        piece.wasMoved = true;

    moves.push_back(std::make_unique<Move>(
        piece, static_cast<sf::Vector2i>(piece.getPosition()), newPosition));

    SoundManager::playSound(SoundKind::MoveSelf);
    board->setLastMoveCells(*moves.back());
    board->updatePiecePosition(piece, newPosition);

    selectedPiece = std::nullopt;
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
        selectedPiece->get().printSelf();
    std::cout << "\n";
}
