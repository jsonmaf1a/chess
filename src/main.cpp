#include "Window.hpp"
#include "shared/FontManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

int main()
{
    FontManager::loadFonts();

    Window window;
    while(window.isOpen())
    {
        window.pollEvents();
        window.update();
    }

    return 0;
}
