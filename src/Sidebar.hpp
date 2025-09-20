#pragma once

#include "GameState.hpp"
#include <SFML/System/Vector2.hpp>
#include <wisp/core/Component.hpp>

class Sidebar : public Component
{
  public:
    Sidebar(sf::RenderWindow &target, sf::FloatRect bounds,
            sf::FloatRect viewport, GameState &state)
        : Component(bounds)
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
