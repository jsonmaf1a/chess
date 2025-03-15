#include "Game.hpp"
#include "Window.hpp"
#include "shared/FontManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

int main()
{
    FontManager::loadFonts();

    UIManager ui;
    Window window(ui);
    Game game(window.getRenderWindow(), ui);

    while(window.isOpen())
    {
        window.pollEvents();
        window.update();
        // game.update()
    }

    return 0;
}
