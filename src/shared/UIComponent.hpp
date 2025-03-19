#pragma once

#include "EventHandler.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>

class UIComponent : public EventHandler
{
  protected:
    UIComponent(sf::FloatRect bounds)
        : id(nextID++)
        , bounds(bounds) {};
    UIComponent(sf::Vector2f size)
        : id(nextID++)
        , bounds(sf::FloatRect({0, 0}, size)) {};
    virtual ~UIComponent() = default;

    sf::FloatRect bounds;
    std::vector<std::shared_ptr<UIComponent>> children;
    std::optional<sf::View> view = std::nullopt;

    int id;
    bool visible = true;
    bool enabled = true;
    UIComponent *parent = nullptr;

    virtual void drawSelf(sf::RenderWindow &window) = 0;

  public:
    virtual void draw(sf::RenderWindow &window);

    void setView(sf::View view) { this->view = view; };
    void setView(sf::FloatRect bounds) { view = sf::View(bounds); };

    EventResult handleEvent(const EventContext &event) override;
    virtual EventResult handleSelfEvent(const EventContext &event)
    {
        return EventResult::Ignored;
    }

    void addChild(std::shared_ptr<UIComponent> child);
    void removeChild(std::shared_ptr<UIComponent> child);
    void printChildren() const;
    void setVisible(bool visible);
    bool isVisible() const;
    void setEnabled(bool enabled);
    bool isEnabled() const;
    void setBounds(const sf::FloatRect &bounds);
    const sf::FloatRect &getBounds() const;

    template <typename T>
    bool viewportContains(const sf::Vector2<T> &position) const
    {
        return view.has_value() && visible && enabled &&
               view->getViewport().contains(sf::Vector2f(position));
    }

  private:
    static inline int nextID = 0;
};
