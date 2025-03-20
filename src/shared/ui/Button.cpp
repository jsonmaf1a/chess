#include "Button.hpp"
#include "../utils/EventUtils.hpp"
#include "../utils/PositionUtils.hpp"
#include <iostream>

void Button::drawSelf(sf::RenderWindow &window)
{
    window.setView(view.value());

    auto bounds = getBounds();
    sf::RectangleShape rect(bounds.size);
    rect.setFillColor(background);

    sf::Text label(font, text, fontSize);
    label.setFillColor(foreground);

    rect.setPosition(bounds.position);
    // label.setPosition(getBounds().position - sf::Vector2f{-100.f, -100.f});
    label.setPosition(bounds.position + bounds.size / 2.f -
                      label.getLocalBounds().size / 2.f);

    window.draw(rect);
    window.draw(label);
}

EventResult Button::handleSelfEvent(const EventContext &eventCtx)
{
    if(EventUtils::isLeftClickEvent(eventCtx.event))
    {
        auto mouseClick = eventCtx.event.getIf<sf::Event::MouseButtonPressed>();
        auto normalizedPosition = PositionUtils::getNormalizedMousePosition(
            mouseClick->position, eventCtx.window);

        if(viewportContains(normalizedPosition))
        {
            return onClick(eventCtx);
        }
    }

    return EventResult::Ignored;
};
