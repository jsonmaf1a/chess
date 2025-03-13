#include "Window.hpp"

#include "Board.hpp"
#include "Sidebar.hpp"
#include <SFML/Window/Cursor.hpp>

Window::Window(uint width, uint height, const std::string &title)
    : width(width)
    , height(height)
    , title(title)
    , cursorManager(window)
{
    window.create(sf::VideoMode({width, height}), title);
    window.setVerticalSyncEnabled(true);

    createRootComponents();

    is_initialized = true;
}

Window::~Window()
{
    if(is_initialized)
    {
        window.close();
    }

    is_initialized = false;
}

void Window::createRootComponents()
{
    // Sidebar
    static constexpr const sf::FloatRect sidebarBounds({0, 0}, {400, 800});
    static constexpr const sf::FloatRect sidebarViewport({0.f, 0.f},
                                                         {1.f / 3.f, 1.0f});
    uiManager.addComponent(
        std::make_shared<Sidebar>(window, sidebarBounds, sidebarViewport));

    // Board
    static constexpr const sf::FloatRect boardBounds({0, 0}, {800, 800});

    static constexpr const sf::FloatRect boardViewport({1.f / 3.f, 0.f},
                                                       {2.f / 3.f, 1.f});
    uiManager.addComponent(
        std::make_shared<Board>(window, boardBounds, boardViewport));
}

void Window::update()
{
    window.clear(BACKGROUND);

    uiManager.draw(window);

    window.display();
}

void Window::handleKeyPress(const sf::Event::KeyPressed &event)
{
    switch(event.code)
    {
        case sf::Keyboard::Key::Escape:
            window.close();
            break;

        default:
            break;
    }
}

void Window::pollEvents()
{
    while(const std::optional event = window.pollEvent())
    {
        if(event->is<sf::Event::Closed>())
            window.close();

        if(auto keyPressedEvent = event->getIf<sf::Event::KeyPressed>())
            handleKeyPress(*keyPressedEvent);

        if(auto mouseEvent = event->getIf<sf::Event::MouseMoved>())
        {
            uiManager.handleEvent(
                EventContext{*mouseEvent, window, cursorManager});
        }

        if(auto mouseEvent = event->getIf<sf::Event::MouseButtonPressed>())
        {
            uiManager.handleEvent(
                EventContext{*mouseEvent, window, cursorManager});
        }

        if(auto mouseEvent = event->getIf<sf::Event::MouseButtonReleased>())
        {
            uiManager.handleEvent(
                EventContext{*mouseEvent, window, cursorManager});
        }
    }
}
