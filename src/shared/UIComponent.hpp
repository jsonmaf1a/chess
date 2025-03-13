#pragma once

#include "Events.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>

class UIComponent
{
  protected:
    sf::FloatRect bounds;
    bool visible = true;
    bool enabled = true;
    std::vector<std::shared_ptr<UIComponent>> children;
    UIComponent *parent = nullptr;

  public:
    UIComponent(sf::FloatRect bounds)
        : bounds(bounds)
        , view(bounds) {};
    virtual ~UIComponent() = default;

    sf::View view;

    void addChild(std::shared_ptr<UIComponent> child);
    void removeChild(std::shared_ptr<UIComponent> child);
    void setVisible(bool visible);
    bool isVisible() const;
    void setEnabled(bool enabled);
    bool isEnabled() const;
    void setBounds(const sf::FloatRect &bounds);
    void drawBoundingBox();
    const sf::FloatRect &getBounds() const;

    bool isMouseOverViewport(sf::Vector2f normalizedMousePos);

    template <typename T>
    bool isViewportContainsPoint(sf::Vector2<T> position) const
    {
        return visible && enabled &&
               view.getViewport().contains(sf::Vector2<float>(position));
    }

    virtual void draw(sf::RenderWindow &window);
    virtual EventResult handleEvent(const EventContext &event);

  protected:
    virtual void drawSelf(sf::RenderWindow &window) = 0;
    virtual EventResult handleSelfEvent(const EventContext &event)
    {
        return EventResult::Ignored;
    }
};
