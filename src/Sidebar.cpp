#include "Sidebar.hpp"

#include "Window.hpp"
#include "shared/utils/PositionUtils.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

void Sidebar::drawSelf(sf::RenderWindow &window)
{
    window.setView(view.value());

    sf::RectangleShape panelViewBg;
    panelViewBg.setSize(sf::Vector2f(400, 800));
    panelViewBg.setPosition({0, 0});
    panelViewBg.setFillColor(Window::BACKGROUND);

    window.draw(panelViewBg);
}

EventResult Sidebar::handleSelfEvent(const EventContext &eventCtx)
{
    if(eventCtx.event.is<sf::Event::MouseMoved>())
    {
        const auto mouseMoved = eventCtx.event.getIf<sf::Event::MouseMoved>();

        auto normalizedPosition = PositionUtils::normalizePosition(
            mouseMoved->position, eventCtx.window);

        // float normX = static_cast<float>((mouseMoved->position.x)) /
        //               eventCtx.window.getSize().x;
        // float normY = static_cast<float>((mouseMoved->position.y)) /
        //               eventCtx.window.getSize().y;

        if(viewportContains(normalizedPosition))
        {
            std::cout << "Sidebar mousemove: "
                      << "x: " << mouseMoved->position.x << "\t"
                      << "y: " << mouseMoved->position.y << "\n";
            return EventResult::Handled;
        }
    }

    return EventResult::Ignored;
}
