#include "../include/states/winState.h"

gameState *winState::eventHandle(sf::RenderWindow &window, statesList &state, sf::Event &event)
{
    if (!winFont.loadFromFile("./assets/fonts/Roboto-Medium.ttf"))
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

gameState *winState::update(sf::RenderWindow &window, statesList &state)
{
    winText[0].setString("GEM : " + to_string(numOfGems));
    winText[1].setString("Star : " + to_string(numOfStars));
    return this;
}

void winState::render(sf::RenderWindow &window)
{
    window.clear();
    window.draw(backgroundSprite);
    for (int i = 0; i < 2; i++)
    {
        window.draw(winText[i]);
    }
}
