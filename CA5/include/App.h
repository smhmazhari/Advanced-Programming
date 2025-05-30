#ifndef TX_APP_GUARD

#define TX_APP_GUARD

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "configs.h"
#include <array>
#include "states/gameState.h"
#include "states/mainMenuState.h"

typedef std::array<gameState *, TX_STATE_NUMBER> statesList;

class App
{
private:
    // main window
    sf::RenderWindow window;
    // current state
    gameState *currentState;
    // statr vector
    statesList states;

public:
    App() : window(sf::VideoMode(TX_WINDOW_WIDTH, TX_WINDOW_HEIGHT), TX_WINDOW_TITLE, sf::Style::Close | sf::Style::Titlebar)
    {
        for (int i = 0; i < TX_STATE_NUMBER; i++)
        {
            states[i] = nullptr;
        }
        currentState = nullptr;
    }
    void init();
    void run();
};

#endif