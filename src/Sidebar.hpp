#pragma once

#include "shared/UIComponent.hpp"

class Sidebar : public UIComponent
{
  public:
    Sidebar(sf::RenderWindow &target, sf::FloatRect bounds,
            sf::FloatRect viewport)
        : UIComponent(bounds)
    {
        view.setViewport(viewport);
    }
    ~Sidebar() = default;

    virtual void drawSelf(sf::RenderWindow &window) override;
    virtual EventResult handleSelfEvent(const EventContext &eventCtx) override;
};
