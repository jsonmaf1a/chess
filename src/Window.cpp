#include "Window.hpp"
#include "shared/utils/EventUtils.hpp"
#include <SFML/Window/Cursor.hpp>

Window::Window(uint width, uint height, const std::string &title)
    : ui(dispatcher)
    , cursorManager(window)
{
    window.create(sf::VideoMode({width, height}), title, sf::Style::None,
                  sf::State::Windowed);
    window.setVerticalSyncEnabled(true);

    ui.init(window);

    isInitialized = true;
}

Window::~Window()
{
    if(isInitialized)
        window.close();

    isInitialized = false;
}

void Window::update()
{
    window.clear(BACKGROUND);

    ui.draw(window);

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

        if(EventUtils::isMouseEvent(event.value()))
        {
            dispatcher.dispatch(
                EventContext{event.value(), window, cursorManager});
            // ui.handleEvent(EventContext{event.value(), window,
            // cursorManager});
        }
    }
}

sf::RenderWindow &Window::getRenderWindow() { return window; }
EventDispatcher &Window::getEventDispatcher() { return dispatcher; }
UIManager &Window::getUI() { return ui; }

bool Window::isOpen() const { return window.isOpen(); }
