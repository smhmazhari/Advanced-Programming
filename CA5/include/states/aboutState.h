#ifndef TX_ABOUT_STATE_GUARD

#define TX_ABOUT_STATE_GUARD

#include "gameState.h"

class aboutState : public gameState
{
private:
public:

    aboutState()
    {
        backgroundPath = "about.png";
        setBackground();
    }

    gameState *eventHandle(sf::RenderWindow &, statesList &, sf::Event &);

    gameState *update(sf::RenderWindow &, statesList &);

    void render(sf::RenderWindow &);
};

#endif
