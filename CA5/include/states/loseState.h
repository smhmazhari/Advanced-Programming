#ifndef TX_LOSE_STATE_GUARD

#define TX_LOSE_STATE_GUARD

#include "gameState.h"

using namespace sf;
using namespace std;

class loseState : public gameState
{
private:
    Font loseFont;
    Text loseText[2];
public:
    loseState()
    {
        backgroundPath = "lose.jpg";
        setBackground();
        for (int i = 0; i < 2; i++)
        {
            loseText[i].setFont(loseFont);
            loseText[i].setFillColor(Color::Red);
            loseText[i].setCharacterSize(40);
            loseText[i].setPosition(1050, 290 + (100 * i));
        }
    }
    gameState *eventHandle(sf::RenderWindow &, statesList &, sf::Event &);

    gameState *update(sf::RenderWindow &, statesList &);

    void render(sf::RenderWindow &);
};

#endif
