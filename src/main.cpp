#define DEBUG

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

int main()
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

    Window window;
    auto &ui = window.getUI();
    auto &renderWindow = window.getRenderWindow();

    auto game = std::make_shared<Game>(renderWindow, ui);
    window.getEventDispatcher().registerListener(game);

    auto sidebar = std::make_shared<Sidebar>(
        renderWindow, LayoutConfig::SidebarBounds,
        LayoutConfig::SidebarViewport, game->getState());
    ui.addComponent(sidebar);

    while(window.isOpen())
    {
        window.pollEvents();
        window.update();
        game->update();
    }

    return 0;
}
