#pragma once

#include "utils/UIComponent.hpp"
#include <memory>
#include <vector>

class UIManager
{
  private:
    std::vector<std::shared_ptr<UIComponent>> rootComponents;

  public:
    void addComponent(std::shared_ptr<UIComponent> component);
    void removeComponent(std::shared_ptr<UIComponent> component);
    void handleEvent(const sf::Event &event);
    void draw(sf::RenderWindow &window);
};
