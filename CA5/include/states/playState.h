#ifndef TX_PLAY_STATE_GUARD

#define TX_PLAY_STATE_GUARD

#include "gameState.h"

class playState : public gameState
{
private:
    bool endGame;

public:
    playState()
    {
        endGame = false;
        backgroundPath = "gamePlay.png";
        setBackground();
    }
    gameState *eventHandle(sf::RenderWindow &, statesList &, sf::Event &);

    gameState *update(sf::RenderWindow &, statesList &);

    void render(sf::RenderWindow &);
};

#endif
