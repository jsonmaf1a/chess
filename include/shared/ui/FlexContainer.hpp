#pragma once

#include "../UIComponent.hpp"

enum class Alignment
{
    Horizontal,
    Vertical
};

class FlexContainer : public UIComponent
{
  public:
    FlexContainer(sf::FloatRect bounds, Alignment alignment)
        : UIComponent(bounds)
    {
        enableView();
    };
    ~FlexContainer();

    virtual void drawSelf(sf::RenderWindow &window) override
    {
        for(auto child : children)
        {
            // TODO:...
        }
    };

  private:
};
