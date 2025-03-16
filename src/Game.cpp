#include "Game.hpp"
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
            return EventResult::Ignored;

        auto cellPosition =
            board->getCellFromMousePos(mousePos, window, board->getView());

        auto piece = board->getPiece(cellPosition);

        if(piece && piece->getSide() == currentSide)
        {
            auto side = piece->getSide() == Side::White ? "white" : "black";
            std::cout << Piece::pieceTypeToString(piece->getKind()) << " "
                      << side << "\n";
            selectedPiece = *piece;
        }
        else
            std::cout << "nothing" << "\n";
    }

    return EventResult::Ignored;
}
