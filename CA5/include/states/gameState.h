#ifndef TX_GAME_STATE

#define TX_GAME_STATE

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <string>
#include "../configs.h"
#include <iostream>
#include <string>

enum state
{
    _mainMenuState = 0,
    _playState,
    _aboutState,
    _exit,
    _chooseMapState,
    _winState,
    _loseState,
    _pauseState
};
class gameState
{
private:
protected:
    int numOfGems;
    int numOfStars;
    std::string backgroundPath;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
public:
    typedef std::array<gameState *, TX_STATE_NUMBER> statesList;
    virtual gameState *eventHandle(sf::RenderWindow &, statesList &, sf::Event &) = 0;
    virtual gameState *update(sf::RenderWindow &, statesList &) = 0;
    virtual void render(sf::RenderWindow &) = 0;
    void setBackground();
    void setNumOfGems(int numOfCollectedGems);
    void setNumOfStar(int numOfCollectedStars);
};
#endif