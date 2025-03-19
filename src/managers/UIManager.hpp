#pragma once

#include "../shared/UIComponent.hpp"
#include "EventDispatcher.hpp"
#include <memory>
#include <vector>

class UIManager
{
  public:
    UIManager(EventDispatcher &dispatcher)
        : dispatcher(dispatcher) {};

    void addComponent(std::shared_ptr<UIComponent> component);
    void removeComponent(std::shared_ptr<UIComponent> component);
    void handleEvent(const EventContext &event);
    void draw(sf::RenderWindow &window);
    void init(sf::RenderWindow &window);

  private:
    std::vector<std::shared_ptr<UIComponent>> rootComponents;
    EventDispatcher &dispatcher;
    sf::Clock clock;
};
