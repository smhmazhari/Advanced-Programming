#ifndef TX_MAIN_MENU_STATE_GUARD

#define TX_MAIN_MENU_STATE_GUARD

#include "gameState.h"

using namespace std;
using namespace sf;

class mainMenuState : public gameState
{
private:
    int mainMenuSelected;
    Font mainMenuFont;
    Text mainMenuText[MAINMENUOPTIONNUMBER];

public:
    mainMenuState()
    {
        backgroundPath = "mainMenu.png";
        setBackground();
        for (int i = 0; i < MAINMENUOPTIONNUMBER; i++)
        {
            mainMenuText[i].setFont(mainMenuFont);
            mainMenuText[i].setFillColor(Color::Yellow);
            mainMenuText[i].setCharacterSize(40);
            mainMenuText[i].setPosition(140, 100 + (100 * i));
        }
        mainMenuText[0].setString("PLAY");
        mainMenuText[1].setString("ABOUT");
        mainMenuText[2].setString("EXIT");

        mainMenuSelected = 0;
    }

    gameState *eventHandle(RenderWindow &, statesList &, sf::Event &);

    gameState *update(RenderWindow &, statesList &);

    void render(RenderWindow &);

    void moveUp();

    void moveDown();
};

#endif