#pragma once

#include "GameState.hpp"
#include "managers/ThemeManager.hpp"
#include "shared/UIComponent.hpp"

#include "shared/ui/Button.hpp"
#include <iostream>

class Sidebar : public UIComponent
{
  public:
    Sidebar(sf::RenderWindow &target, sf::FloatRect bounds,
            sf::FloatRect viewport, GameState &state)
        : UIComponent(bounds)
        , state(state)
    {
        setView(bounds);
        view->setViewport(viewport);

        auto button = std::make_shared<Button>(
            sf::FloatRect({0, 0}, {bounds.size.x, bounds.size.y / 8.f}),
            "Button",
            [&](const EventContext &eventCtx) {
                std::cout << "click\n";

                state.isPlaying = state.isPlaying ? false : true;
                state.initializeClocks();

                return EventResult::Handled;
            },
            sf::Color::Black, sf::Color::White, FontStyle::Semibold, 32);

        auto enableNeonThemeButton = std::make_shared<Button>(
            sf::FloatRect({0, bounds.size.y / 8.f},
                          {bounds.size.x / 2.f, bounds.size.y / 8.f}),
            "Apply neon theme",
            [&](const EventContext &eventCtx) {
                std::cout << "apply neon\n";
                ThemeManager::setTheme(ThemeID::Neon);

                return EventResult::Handled;
            },
            sf::Color::Black, sf::Color::White, FontStyle::Semibold, 12);

        auto enableDefaultThemeButton = std::make_shared<Button>(
            sf::FloatRect({bounds.size.x / 2.f, bounds.size.y / 8.f},
                          {bounds.size.x / 2.f, bounds.size.y / 8.f}),
            "Apply default theme",
            [&](const EventContext &eventCtx) {
                std::cout << "apply default\n";
                ThemeManager::setTheme(ThemeID::Default);

                return EventResult::Handled;
            },
            sf::Color::Black, sf::Color::White, FontStyle::Semibold, 12);

        addChild(button);
        addChild(enableNeonThemeButton);
        addChild(enableDefaultThemeButton);
    }
    ~Sidebar() = default;

    virtual void drawSelf(sf::RenderWindow &window) override;
    virtual EventResult handleSelfEvent(const EventContext &eventCtx) override;

  private:
    GameState &state;
};
