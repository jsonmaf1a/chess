#include "Button.hpp"
#include "../utils/EventUtils.hpp"
#include "../utils/PositionUtils.hpp"
#include <iostream>

void Button::drawSelf(sf::RenderWindow &window)
{
    auto normPos = PositionUtils::normalizePosition(bounds.position, window);
    auto normSize = PositionUtils::normalizePosition(bounds.size, window);

    view->setViewport({normPos, normSize});
    window.setView(view.value());

    auto bounds = getBounds();
    sf::RectangleShape rect(bounds.size);
    rect.setPosition(bounds.position);
    rect.setFillColor(background);

    sf::Text label(font, text, fontSize);
    label.setOrigin({label.getLocalBounds().position.x,
                     label.getLocalBounds().size.y / 2.f});
    label.setPosition(bounds.position + bounds.size / 2.f -
                      label.getLocalBounds().size / 2.f);
    label.setFillColor(foreground);

    sf::RectangleShape labelBounds(label.getLocalBounds().size);
    labelBounds.setOutlineColor(sf::Color::Green);
    labelBounds.setOutlineThickness(1.2f);
    labelBounds.setFillColor(sf::Color::Transparent);
    labelBounds.setPosition(bounds.position + bounds.size / 2.f -
                            label.getLocalBounds().size / 2.f);

    window.draw(rect);
    window.draw(label);
    // window.draw(labelBounds);
}

EventResult Button::handleSelfEvent(const EventContext &eventCtx)
{
    if(EventUtils::isLeftClickEvent(eventCtx.event))
    {
        auto mouseClick = eventCtx.event.getIf<sf::Event::MouseButtonPressed>();
        auto normalizedPosition = PositionUtils::normalizePosition(
            mouseClick->position, eventCtx.window);

        if(viewportContains(normalizedPosition))
        {
            return onClick(eventCtx);
        }
    }

    if(eventCtx.event.is<sf::Event::MouseMoved>())
    {
        auto mouseMoved = eventCtx.event.getIf<sf::Event::MouseMoved>();
        auto normalizedPosition = PositionUtils::normalizePosition(
            mouseMoved->position, eventCtx.window);

        if(viewportContains(normalizedPosition))
        {
            std::cout << "mouse over: " << id << "\n";
        }
    }
    return EventResult::Ignored;
};
