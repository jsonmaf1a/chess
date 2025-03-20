#pragma once

#include "../../managers/FontManager.hpp"
#include "../UIComponent.hpp"
#include "../config/Layout.hpp"
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
        setView(bounds);
        view->setViewport(sf::FloatRect(
            {0.f, 0.f}, {LayoutConfig::SidebarViewport.size.x,
                         LayoutConfig::SidebarViewport.size.y / 8.f}));
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
