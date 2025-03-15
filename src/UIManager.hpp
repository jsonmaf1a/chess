#pragma once

#include "Board.hpp"
#include "Sidebar.hpp"
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

    Board &getBoard() const;
    Sidebar &getSidebar() const;
};
