#include "../include/states/playState.h"
#include "../include/states/loseState.h"
#include "../include/states/winState.h"

gameState *playState::eventHandle(sf::RenderWindow &window, statesList &state, sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            return state[_mainMenuState];
        }
        if (event.key.code == sf::Keyboard::W)
        {

            if (state[_winState])
            {
                delete state[_winState];
            }
            state[_winState] = new winState();
            return state[_winState];
        }
        if (event.key.code == sf::Keyboard::L)
        {
            if (state[_loseState])
            {
                delete state[_loseState];
            }
            state[_loseState] = new loseState();
            return state[_loseState];
        }
    }

    return this;
}

gameState *playState::update(sf::RenderWindow &window, statesList &state)
{
    return this;
}

void playState::render(sf::RenderWindow &window)
{
    window.clear();
    window.draw(backgroundSprite);
}
