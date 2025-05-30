#include "../include/states/aboutState.h"



gameState* aboutState::eventHandle(sf::RenderWindow& window, statesList& state , sf::Event& event)
{    
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            return state[_mainMenuState];
        }
    }   
    return this;
}

gameState* aboutState::update(sf::RenderWindow& window,statesList &state)
{
    return this;
}

void aboutState::render(sf::RenderWindow& window)
{
    window.clear();
    window.draw(backgroundSprite);
}
