#pragma once

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>

enum class EventResult
{
    Ignored,
    Handled, //  NOTE: event was handled, but can continue propagation
    Consumed //  NOTE: event was handled and should stop propagation
};

class UIComponent
{
  protected:
    sf::FloatRect bounds;
    bool visible = true;
    bool enabled = true;
    std::vector<std::shared_ptr<UIComponent>> childrens;
    UIComponent *parent = nullptr;

  public:
    UIComponent(sf::FloatRect bounds)
        : bounds(bounds) {};
    virtual ~UIComponent() = default;

    void addChild(std::shared_ptr<UIComponent> child);
    void removeChild(std::shared_ptr<UIComponent> child);
    bool contains(float x, float y) const;
    void setVisible(bool visible);
    bool isVisible() const;
    void setEnabled(bool enabled);
    bool isEnabled() const;
    void setBounds(const sf::FloatRect &bounds);
    const sf::FloatRect &getBounds() const;

    virtual void draw(sf::RenderWindow &window);
    virtual EventResult handleEvent(const sf::Event &event);

  protected:
    virtual void drawSelf(sf::RenderWindow &window) = 0;
    virtual EventResult handleSelfEvent(const sf::Event &event)
    {
        return EventResult::Ignored;
    }
};
