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

        auto maybePiece = board->getPiece(cellPosition);

        if(maybePiece && maybePiece->getSide() == currentSide)
        {
            selectedPiece = *maybePiece;
            board->setSelectedCell(cellPosition);

            auto side = selectedPiece->get().getSide() == Side::White ? "white"
                                                                      : "black";
            // std::cout << Piece::pieceKindToString(piece->getKind()) << " "
            //           << side << "\n";

            std::cout << Piece::pieceKindToString(
                             selectedPiece->get().getKind())
                      << " " << side << "\n";
        }
        else if(selectedPiece && !maybePiece)
        {
            move(selectedPiece->get(), cellPosition);
        }
        else
        {
            selectedPiece = std::nullopt;
            std::cout << "nothing" << "\n";
        }
    }

    return EventResult::Ignored;
}

void Game::move(Piece &piece, sf::Vector2i newPosition)
{
    if(!piece.isLegalMove(newPosition))
    {
        board->resetSelectedCell();
        return;
    }

    if(!piece.wasMoved)
        piece.wasMoved = true;

    moves.push_back(
        std::make_unique<Move>(piece, piece.getPosition(), newPosition));

    SoundManager::playSound(SoundKind::MoveSelf);

    board->highlightMove(*moves.back());
    board->updatePiecePosition(selectedPiece.value(), newPosition);
    board->dumpSelf();
    board->dumpChildren();

    selectedPiece = std::nullopt;
    nextTurn();
}

void Game::nextTurn()
{
    currentSide = currentSide == Side::White ? Side::Black : Side::White;
}
