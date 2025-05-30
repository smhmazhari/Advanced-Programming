#include "../include/states/playState.h"
#include "../include/states/loseState.h"
#include "../include/states/winState.h"
#include "../include/states/puaseState.h"

gameState *pauseState::eventHandle(sf::RenderWindow &window, statesList &state, sf::Event &event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::R)
        {
            state[_playState] = new playState();
            return state[_playState];
        }
    }
    return this;
}

gameState *pauseState::update(sf::RenderWindow &window, statesList &state)
{
    return this;
}

void pauseState::render(sf::RenderWindow &window)
{
    window.draw(backgroundSprite);
}
