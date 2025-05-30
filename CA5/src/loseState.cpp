
#include "../include/states/loseState.h"

gameState *loseState::eventHandle(sf::RenderWindow &window, statesList &state, sf::Event &event)
{
    if (!loseFont.loadFromFile("./assets/fonts/Roboto-Medium.ttf"))
    {
        cout << "No font is here!";
    }
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            return state[_mainMenuState];
        }
        if (event.key.code == sf::Keyboard::Enter)
        {
            window.close();
        }
    }
    return this;
}

gameState *loseState::update(sf::RenderWindow &window, statesList &state)
{
    loseText[0].setString("GEM : " + to_string(numOfGems));
    loseText[1].setString("Star : " + to_string(numOfStars));
    return this;
}

void loseState::render(sf::RenderWindow &window)
{
    window.clear();
    window.draw(backgroundSprite);
    for (int i = 0; i < 2; i++)
    {
        window.draw(loseText[i]);
    }
}
