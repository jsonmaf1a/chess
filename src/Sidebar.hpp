#pragma once

#include "shared/UIComponent.hpp"

#include "shared/ui/Button.hpp"
#include <iostream>

class Sidebar : public UIComponent
{
  public:
    Sidebar(sf::RenderWindow &target, sf::FloatRect bounds,
            sf::FloatRect viewport)
        : UIComponent(bounds)
    {
        setView(bounds);
        view->setViewport(viewport);

        auto button = std::make_shared<Button>(
            sf::FloatRect({0, 0}, {bounds.size.x, bounds.size.y / 8.f}),
            "penis",
            [](const EventContext &eventCtx) {
                std::cout << "click\n";
                return EventResult::Handled;
            },
            sf::Color::Black, sf::Color::Green);

        addChild(button);
    }
    ~Sidebar() = default;

    virtual void drawSelf(sf::RenderWindow &window) override;
    virtual EventResult handleSelfEvent(const EventContext &eventCtx) override;
};
