#ifndef TX_PAUSE_STATE_GUARD

#define TX_PAUSE_STATE_GUARD

#include "gameState.h"

class pauseState : public gameState
{
private:
    bool endGame;

public:
    pauseState()
    {
        endGame = false;
        backgroundPath = "pause.png";
        setBackground();
    }
    gameState *eventHandle(sf::RenderWindow &, statesList &, sf::Event &);

    gameState *update(sf::RenderWindow &, statesList &);

    void render(sf::RenderWindow &);
};

#endif
