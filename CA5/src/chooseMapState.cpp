#include "../include/states/chooseMapState.h"
#include "../include/states/playState.h"

using namespace std;

gameState *chooseMapState::eventHandle(sf::RenderWindow &window, statesList &state, sf::Event &event)
{

    if (!menuFont.loadFromFile("./assets/fonts/Roboto-Medium.ttf"))
    {
        cout << "No font is here!";
    }

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up)
        {
            this->moveUp();
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
            this->moveDown();
        }
        else if (event.key.code == sf::Keyboard::Enter)
        {
            // creat play state
            if (state[_playState])
            {
                delete state[_playState];
            }
            state[_playState] = new playState();
            return state[_playState];
        }
        else if (event.key.code == sf::Keyboard::Escape)
        {
            if (event.key.code == sf::Keyboard::Escape)
        {
            return state[_mainMenuState];
        }
        }
        
    }
    return this;
}

gameState *chooseMapState::update(sf::RenderWindow &window, statesList &state)
{
    return this;
}

void chooseMapState::render(sf::RenderWindow &window)
{
    window.draw(backgroundSprite);
    for (int i = 0; i < MAINMENUOPTIONNUMBER; i++)
    {
        window.draw(maps[i]);
    }
}

void chooseMapState::moveUp()
{
    if (selectedMap - 1 >= 0)
    {
        maps[selectedMap].setFillColor(Color::Yellow);
        selectedMap--;
        if (selectedMap == -1)
        {
            selectedMap = 2;
        }
        maps[selectedMap].setFillColor(Color::Black);
    }
}

void chooseMapState::moveDown()
{
    if (selectedMap + 1 <= MAINMENUOPTIONNUMBER)
    {
        maps[selectedMap].setFillColor(Color::Yellow);
        selectedMap++;
        if (selectedMap == 3)
        {
            selectedMap = 0;
        }
        maps[selectedMap].setFillColor(Color::Black);
    }
}
