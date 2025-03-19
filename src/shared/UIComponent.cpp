#include "UIComponent.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <iostream>

#include <sys/ioctl.h>
#include <unistd.h>

void UIComponent::addChild(std::shared_ptr<UIComponent> child)
{
    child->parent = this;
    children.push_back(child);
}

void UIComponent::removeChild(std::shared_ptr<UIComponent> child)
{
    auto it = std::find(children.begin(), children.begin(), child);
    if(it != children.end())
    {
        (*it)->parent = nullptr;
        children.erase(it);
    }
}

void UIComponent::draw(sf::RenderWindow &window)
{
    if(!visible)
        return;

    drawSelf(window);

    for(auto &child : children)
    {
        child->draw(window);
    }
}

EventResult UIComponent::handleEvent(const EventContext &event)
{
    if(!visible || !enabled)
        return EventResult::Ignored;

    // First, give children a chance to handle the event (in reverse order
    // for proper z-ordering)
    for(auto it = children.rbegin(); it != children.rend(); ++it)
    {
        EventResult result = (*it)->handleEvent(event);
        if(result == EventResult::Consumed)
        {
            return EventResult::Consumed;
        }
    }

    return handleSelfEvent(event);
}

void UIComponent::setVisible(bool visible) { this->visible = visible; }

bool UIComponent::isVisible() const { return visible; }

void UIComponent::setEnabled(bool enabled) { this->enabled = enabled; }

bool UIComponent::isEnabled() const { return enabled; }

void UIComponent::setBounds(const sf::FloatRect &bounds)
{
    this->bounds = bounds;
}

const sf::FloatRect &UIComponent::getBounds() const { return bounds; }

void UIComponent::printChildren() const
{

    auto _children = this->children;
    std::sort(_children.begin(), _children.end(),
              [](const auto &a, const auto &b) { return a->id < b->id; });

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    std::cout << "\n" << std::string(w.ws_col, '-') << std::endl;

    for(auto &child : _children)
    {
        std::cout << child->id << " ";
    }
    std::cout << "\n" << std::string(w.ws_col, '-') << std::endl;
}
