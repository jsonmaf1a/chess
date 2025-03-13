#include "Window.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

int main()
{
    Window window;

    while(window.isOpen())
    {
        window.pollEvents();
        window.update();
    }

    return 0;
}
