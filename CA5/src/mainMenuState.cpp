#include "../include/states/mainMenuState.h"
#include "../include/states/playState.h"
#include "../include/states/chooseMapState.h"
#include "../include/states/aboutState.h"
#include "../include/states/exitState.h"
using namespace std;

gameState *mainMenuState::eventHandle(sf::RenderWindow &window, statesList &state, sf::Event &event)
{

    if (!mainMenuFont.loadFromFile("./assets/fonts/Roboto-Medium.ttf"))
    {
        cout << "No font is here!";
    }

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Space)
        {
            if (state[_playState])
            {
                delete state[_playState];
            }
            state[_playState] = new playState();
            return state[_playState];
        }
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
            if (mainMenuSelected == 0)
            {
                if (state[_chooseMapState])
                {
                    delete state[_chooseMapState];
                }
                state[_chooseMapState] = new chooseMapState();
                return state[_chooseMapState];
            }
            if (mainMenuSelected == 1)
            {
                if (state[_aboutState])
                {
                    delete state[_aboutState];
                }
                state[_aboutState] = new aboutState();
                return state[_aboutState];
            }
            if (mainMenuSelected == 2)
            {
                window.close();
                if (state[_exit])
                {
                    delete state[_exit];
                }
                state[_exit] = new exitState();
                return state[_exit];
            }
        }
    }
    return this;
}

gameState *mainMenuState::update(sf::RenderWindow &window, statesList &state)
{
    return this;
}

void mainMenuState::render(sf::RenderWindow &window)
{
    window.draw(backgroundSprite);
    for (int i = 0; i < MAINMENUOPTIONNUMBER; i++)
    {
        window.draw(mainMenuText[i]);
    }
}

void mainMenuState::moveUp()
{
    if (mainMenuSelected - 1 >= 0)
    {
        mainMenuText[mainMenuSelected].setFillColor(Color::Yellow);
        mainMenuSelected--;
        if (mainMenuSelected == -1)
        {
            mainMenuSelected = 2;
        }
        mainMenuText[mainMenuSelected].setFillColor(Color::Black);
    }
}

void mainMenuState::moveDown()
{
    if (mainMenuSelected + 1 <= MAINMENUOPTIONNUMBER)
    {
        mainMenuText[mainMenuSelected].setFillColor(Color::Yellow);
        mainMenuSelected++;
        if (mainMenuSelected == 3)
        {
            mainMenuSelected = 0;
        }
        mainMenuText[mainMenuSelected].setFillColor(Color::Black);
    }
}
