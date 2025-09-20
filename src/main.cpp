#include "Game.hpp"
#include "Sidebar.hpp"
#include "config/Layout.hpp"
#include "managers/FontManager.hpp"
#include "managers/SoundManager.hpp"
#include "managers/ThemeManager.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <wisp/core/Window.hpp>

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

int main()
{
    if(preloadAssets() != 0)
        return -1;

    Window window(LayoutConfig::WindowSize.x, LayoutConfig::WindowSize.y);

    auto &ui = window.getUI();
    auto &renderWindow = window.getRenderWindow();

    auto game = std::make_shared<Game>(renderWindow, ui);

    window.getEventDispatcher().registerListener(game);

    // NOTE: temporary ↓
    auto &gameState = game->getState();
    gameState.isPlaying = true;
    // gameState.hasGameStarted = true;
    gameState.initializeTimers();
    // NOTE: temporary ↑

    auto sidebar =
        std::make_shared<Sidebar>(renderWindow, LayoutConfig::SidebarBounds,
                                  LayoutConfig::SidebarViewport, gameState);
    ui.addComponent(sidebar);

    // sidebar->addButtons();

    while(window.isOpen())
    {
        window.pollEvents();
        window.update();
        game->update();
    }

    return 0;
}
