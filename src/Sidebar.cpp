#include "Sidebar.hpp"

#include "managers/FontManager.hpp"
#include "managers/ThemeManager.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>
#include <string>
#include <wisp/ui/Button.hpp>
#include <wisp/utils/PositionUtils.hpp>

void Sidebar::addButtons()
{

    auto button = std::make_shared<Button>(
        sf::Vector2f{bounds.size.x, bounds.size.y / 8.f}, "Play",
        FontManager::getFont(FontStyle::Regular));

    auto onClick = [&, button](const EventContext &eventCtx) {
        std::cout << "click\n";

        state.isPlaying = state.isPlaying ? false : true;
        button->setText(state.isPlaying ? "Pause" : "Play");

        return EventResult::Handled;
    };
    button->setOnClick(onClick);

    auto enableNeonThemeButton = std::make_shared<Button>(
        sf::Vector2f{bounds.size.x / 2.f, bounds.size.y / 8.f},
        "Apply neon theme", FontManager::getFont(FontStyle::Regular));

    enableNeonThemeButton->setOnClick([&](const EventContext &eventCtx) {
        std::cout << "apply neon\n";
        ThemeManager::setTheme(ThemeID::Neon);

        return EventResult::Handled;
    });

    auto enableDefaultThemeButton = std::make_shared<Button>(
        sf::Vector2f{bounds.size.x / 2.f, bounds.size.y / 8.f},
        "Apply default theme", FontManager::getFont(FontStyle::Regular));

    enableDefaultThemeButton->setOnClick([&](const EventContext &eventCtx) {
        std::cout << "apply default\n";
        ThemeManager::setTheme(ThemeID::Default);

        return EventResult::Handled;
    });

    addChild(button);
    addChild(enableNeonThemeButton);
    addChild(enableDefaultThemeButton);

    button->enableView();
    enableNeonThemeButton->enableView();
    enableDefaultThemeButton->enableView();
}

void Sidebar::drawSelf(sf::RenderWindow &window)
{
    window.setView(view.value());

    sf::RectangleShape panelViewBg;
    panelViewBg.setSize(bounds.size);
    panelViewBg.setPosition({0, 0});
    panelViewBg.setFillColor(ThemeManager::getTheme().ui.background);

    auto whiteSeconds = state.whiteTimer.millis.count() / 1000;
    sf::Text white(FontManager::getFont(FontStyle::Regular),
                   "white: " + std::to_string(whiteSeconds), 20);
    white.setOrigin(white.getLocalBounds().position);
    white.setPosition({bounds.position.x + bounds.size.x / 2.f -
                           white.getGlobalBounds().size.x / 2.f,
                       bounds.position.y + bounds.size.y / 2.f -
                           white.getGlobalBounds().size.y / 2.f});
    white.setFillColor(ThemeManager::getTheme().ui.foreground);

    auto blackSeconds = state.blackTimer.millis.count() / 1000;
    sf::Text black(FontManager::getFont(FontStyle::Regular),
                   "black: " + std::to_string(blackSeconds), 20);
    black.setOrigin(black.getLocalBounds().position);
    black.setPosition({bounds.position.x + bounds.size.x / 2.f -
                           black.getGlobalBounds().size.x / 2.f,
                       bounds.position.y + bounds.size.y / 2.f -
                           black.getGlobalBounds().size.y / 2.f +
                           white.getLocalBounds().size.y + 10.f});
    black.setFillColor(ThemeManager::getTheme().ui.foreground);

    window.draw(panelViewBg);
    window.draw(white);
    window.draw(black);
}

EventResult Sidebar::handleSelfEvent(const EventContext &eventCtx)
{
    if(eventCtx.event.is<sf::Event::MouseMoved>())
    {
        const auto mouseMoved = eventCtx.event.getIf<sf::Event::MouseMoved>();

        auto normalizedPosition = PositionUtils::normalizePosition(
            mouseMoved->position, eventCtx.window);

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
