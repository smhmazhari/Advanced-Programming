#include "../include/states/exitState.h"



gameState* exitState::eventHandle(sf::RenderWindow& window, statesList& state , sf::Event& event)
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

gameState* exitState::update(sf::RenderWindow& window,statesList &state)
{
    return this;
}

void exitState::render(sf::RenderWindow& window)
{
    window.clear();
    window.draw(backgroundSprite);
    

}
