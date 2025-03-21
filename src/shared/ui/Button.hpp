#pragma once

#include "../../managers/FontManager.hpp"
#include "../UIComponent.hpp"
#include <functional>

class Button : public UIComponent
{
  public:
    Button(sf::FloatRect bounds, std::string label,
           std::function<EventResult(const EventContext &)> onClick,
           sf::Color background, sf::Color foreground,
           FontStyle fontStyle = FontStyle::Regular, unsigned int fontSize = 12)
        : UIComponent(bounds)
        , text(label)
        , onClick(onClick)
        , background(background)
        , foreground(foreground)
        , font(FontManager::getFont(fontStyle))
        , fontSize(fontSize)
    {
        sf::Vector2f normViewportPosition = {
            bounds.position.x / getBounds().position.x,
            bounds.position.y / getBounds().position.y};
        sf::Vector2f normViewportSize = {bounds.size.x / getBounds().size.x,
                                         bounds.size.y / getBounds().size.y};

        setView(bounds);
    };
    ~Button() = default;

    virtual void drawSelf(sf::RenderWindow &window) override;
    virtual EventResult handleSelfEvent(const EventContext &eventCtx) override;

  private:
    std::function<EventResult(const EventContext &)> onClick;
    std::string text;
    sf::Color background;
    sf::Color foreground;
    const sf::Font &font;
    unsigned int fontSize;
};
