#ifndef TX_CHOOSE_MAP_STATE_GUARD

#define TX_CHOOSE_MAP_STATE_GUARD

#include "gameState.h"

using namespace std;
using namespace sf;

class chooseMapState : public gameState
{
private:
    int selectedMap;
    Font menuFont;
    Text maps[NUMOFOPTION];

public:
    chooseMapState()
    {
        backgroundPath = "maxresdefault.jpg";
        setBackground();
        for (int i = 0; i < MAINMENUOPTIONNUMBER; i++)
        {
            maps[i].setFont(menuFont);
            maps[i].setFillColor(Color::Yellow);
            maps[i].setCharacterSize(40);
            maps[i].setPosition(570, 350 + (100 * i));
            // mainMenuText[i].setPosition();
        }
        maps[0].setString("MAP_1");
        maps[1].setString("MAP_2");
        maps[2].setString("MAP_3");

        selectedMap = 0;
    }
    
    gameState *eventHandle(RenderWindow &, statesList &, sf::Event &);

    gameState *update(RenderWindow &, statesList &);

    void render(RenderWindow &);

    void moveUp();

    void moveDown();
};

#endif