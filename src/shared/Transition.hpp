#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>
class Transition
{
  protected:
    float duration;
    float elapsedTime = 0;
    bool _isFinished = false;

  public:
    Transition(float duration)
        : duration(duration)
    {}

    virtual void update(float dt)
    {
        elapsedTime += dt;
        if(elapsedTime >= duration)
        {
            _isFinished = true;
            elapsedTime = duration;
        }
    }

    bool isFinished() const { return _isFinished; }
};
