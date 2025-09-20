#pragma once

#include "../../managers/FontManager.hpp"
#include "../../managers/ThemeManager.hpp"
#include "../UIComponent.hpp"
#include <SFML/System/Vector2.hpp>
#include <functional>

class Button : public UIComponent
{
  public:
    Button(sf::Vector2f size, std::string label,
           FontStyle fontStyle = FontStyle::Regular, unsigned int fontSize = 14)
        : UIComponent(size)
        , text(label)
        , background(ThemeManager::getTheme().ui.accent)
        , foreground(ThemeManager::getTheme().ui.foreground)
        , font(FontManager::getFont(fontStyle))
        , fontSize(fontSize) {
            // setView(bounds);
        };
    ~Button() = default;

    void setText(std::string text);
    void setOnClick(std::function<EventResult(const EventContext &)> onClick);
    virtual void drawSelf(sf::RenderWindow &window) override;
    virtual EventResult handleSelfEvent(const EventContext &eventCtx) override;

  private:
    std::function<EventResult(const EventContext &)> onClick;
    std::string text;
    sf::Color background;
    sf::Color foreground;
    const sf::Font &font;
    unsigned int fontSize;

    void drawLabel(sf::RenderWindow &window);
    void drawBackground(sf::RenderWindow &window);
};
