#ifndef TX_EXIT_STATE_GUARD

#define TX_EXIT_STATE_GUARD

#include "gameState.h"

class exitState : public gameState
{
private:
public:
    gameState *eventHandle(sf::RenderWindow &, statesList &, sf::Event &);

    gameState *update(sf::RenderWindow &, statesList &);

    void render(sf::RenderWindow &);
};

#endif
