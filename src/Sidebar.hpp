#pragma once

#include "GameState.hpp"
#include "shared/UIComponent.hpp"
#include <SFML/System/Vector2.hpp>

class Sidebar : public UIComponent
{
  public:
    Sidebar(sf::RenderWindow &target, sf::FloatRect bounds,
            sf::FloatRect viewport, GameState &state)
        : UIComponent(bounds)
        , state(state)
    {
        enableView();
        // setView(bounds);
        view->setViewport(viewport);
    }
    ~Sidebar() = default;

    virtual void drawSelf(sf::RenderWindow &window) override;
    virtual EventResult handleSelfEvent(const EventContext &eventCtx) override;
    void addButtons();

  private:
    GameState &state;
};
