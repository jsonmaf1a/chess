#include "UIManager.hpp"

void UIManager::addComponent(std::shared_ptr<UIComponent> component)
{
    rootComponents.push_back(component);
}

void UIManager::removeComponent(std::shared_ptr<UIComponent> component)
{
    auto it =
        std::find(rootComponents.begin(), rootComponents.end(), component);
    if(it != rootComponents.end())
    {
        rootComponents.erase(it);
    }
}

void UIManager::handleEvent(const sf::Event &event)
{
    for(auto it = rootComponents.rbegin(); it != rootComponents.rend(); ++it)
    {
        EventResult result = (*it)->handleEvent(event);
        if(result == EventResult::Consumed)
        {
            break;
        }
    }
}

void UIManager::draw(sf::RenderWindow &window)
{
    for(auto &component : rootComponents)
    {
        component->draw(window);
    }
}
