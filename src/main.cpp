#include "Game.hpp"
#include "Window.hpp"
#include "managers/FontManager.hpp"
#include "managers/SoundManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

int preloadAssets()
{
    try
    {
        FontManager::loadFonts();
        SoundManager::loadSounds();
    }
    catch(const std::exception &e)
    {
        std::cerr << "Error during asset preloading: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}

int main()
{
    if(preloadAssets() != 0)
    {
        std::cerr << "Asset loading failed. Exiting program." << std::endl;
        return -1;
    }

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
