#include "Game.hpp"
#include "Window.hpp"
#include "managers/FontManager.hpp"
#include "managers/SoundManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

int main()
{
    try
    {
        FontManager::loadFonts();
        SoundManager::loadSounds();
    }
    catch(const std::exception &e)
    {
        std::cerr << "Error during asset preloading: " << e.what() << "\n";
        std::cerr << "Exiting game.\n";

        return -1;
    }

    Window window;

    auto game =
        std::make_shared<Game>(window.getRenderWindow(), window.getUI());
    window.getEventDispatcher().registerListener(game);

    game->start();

    while(window.isOpen())
    {
        window.pollEvents();
        window.update();
    }

    return 0;
}
