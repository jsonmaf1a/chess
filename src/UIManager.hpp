#pragma once

#include "shared/UIComponent.hpp"
#include <memory>
#include <vector>

class UIManager
{
  private:
    std::vector<std::shared_ptr<UIComponent>> rootComponents;

  public:
    void addComponent(std::shared_ptr<UIComponent> component);
    void removeComponent(std::shared_ptr<UIComponent> component);
    void handleEvent(const EventContext &event);
    void draw(sf::RenderWindow &window);
};
