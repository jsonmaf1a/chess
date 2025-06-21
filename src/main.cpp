#include "Game.hpp"
#include "Sidebar.hpp"
#include "Window.hpp"
#include "managers/FontManager.hpp"
#include "managers/SoundManager.hpp"
#include "managers/ThemeManager.hpp"
#include "shared/config/Layout.hpp"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

int preloadAssets()
{
    try
    {
        FontManager::loadFonts();
        SoundManager::loadSounds();
        ThemeManager::loadThemes();
    }
    catch(const std::exception &e)
    {
        std::cerr << "Error during asset preloading: " << e.what() << "\n";
        std::cerr << "Exiting game.\n";

        return -1;
    }

    return 0;
}

int initialize(Window &window, std::shared_ptr<Game> &game)
{
    if(preloadAssets() != 0)
        return -1;

    auto &ui = window.getUI();
    auto &renderWindow = window.getRenderWindow();

    game = std::make_shared<Game>(renderWindow, ui);
    window.getEventDispatcher().registerListener(game);

    auto sidebar = std::make_shared<Sidebar>(
        renderWindow, LayoutConfig::SidebarBounds,
        LayoutConfig::SidebarViewport, game->getState());
    ui.addComponent(sidebar);

    sidebar->addButtons();

    return 0;
}

int main()
{
    Window window;
    std::shared_ptr<Game> game;
https: // www.youtube.com/watch?v=08C987fQEKU
    if(initialize(window, game) != 0)
        return -1;

    while(window.isOpen())
    {
        window.pollEvents();
        window.update();
        game->update();
    }

    return 0;
}
