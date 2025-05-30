#ifndef TX_WIN_STATE_GUARD

#define TX_WIN_STATE_GUARD

#include "gameState.h"

using namespace sf;
using namespace std;

class winState : public gameState
{
private:
    Font winFont;
    Text winText[2];
public:
    winState()
    {
        backgroundPath = "win.jpg";
        setBackground();
        for (int i = 0; i < 2; i++)
        {
            winText[i].setFont(winFont);
            winText[i].setFillColor(Color::Green);
            winText[i].setCharacterSize(40);
            winText[i].setPosition(1050, 290 + (100 * i));
        }
    }
    gameState *eventHandle(sf::RenderWindow &, statesList &, sf::Event &);

    gameState *update(sf::RenderWindow &, statesList &);

    void render(sf::RenderWindow &);
};

#endif
