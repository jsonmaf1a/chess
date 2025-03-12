#include "UIComponent.hpp"
#include <iostream>

void UIComponent::addChild(std::shared_ptr<UIComponent> child)
{
    child->parent = this;
    childrens.push_back(child);
}

void UIComponent::removeChild(std::shared_ptr<UIComponent> child)
{
    auto it = std::find(childrens.begin(), childrens.begin(), child);
    if(it != childrens.end())
    {
        (*it)->parent = nullptr;
        childrens.erase(it);
    }
}

bool UIComponent::contains(float x, float y) const
{
    return visible && enabled && bounds.contains({x, y});
}

void UIComponent::draw(sf::RenderWindow &window)
{
    if(!visible)
        return;

    drawSelf(window);

    for(auto &child : childrens)
    {
        child->draw(window);
    }
}

EventResult UIComponent::handleEvent(const sf::Event &event)
{
    if(!visible || !enabled)
        return EventResult::Ignored;

    // First, give children a chance to handle the event (in reverse order
    // for proper z-ordering)
    for(auto it = childrens.rbegin(); it != childrens.rend(); ++it)
    {
        EventResult result = (*it)->handleEvent(event);
        if(result == EventResult::Consumed)
        {
            return EventResult::Consumed;
        }
    }

    return handleSelfEvent(event);
}

void UIComponent::setVisible(bool visible)
{
    this->visible = visible;
}

bool UIComponent::isVisible() const
{
    return visible;
}

void UIComponent::setEnabled(bool enabled)
{
    this->enabled = enabled;
}

bool UIComponent::isEnabled() const
{
    return enabled;
}

void UIComponent::setBounds(const sf::FloatRect &bounds)
{
    this->bounds = bounds;
}

const sf::FloatRect &UIComponent::getBounds() const
{
    return bounds;
}
