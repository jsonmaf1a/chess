#include "Game.hpp"
#include "Window.hpp"
#include "managers/FontManager.hpp"
#include "managers/SoundManager.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>

void preloadAssets()
{
    FontManager::loadFonts();
    SoundManager::loadSounds();
}

int main()
{
    preloadAssets();

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
