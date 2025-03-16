#include "Game.hpp"
#include "Window.hpp"
#include "shared/FontManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

int main()
{
    FontManager::loadFonts();

    Window window;

    auto game =
        std::make_shared<Game>(window.getRenderWindow(), window.getUI());

    window.getEventDispatcher().registerListener(game);

    while(window.isOpen())
    {
        window.pollEvents();
        window.update();
        // game.update()
    }

    return 0;
}
