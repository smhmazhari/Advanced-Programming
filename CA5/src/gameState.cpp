#include "../include/states/gameState.h"
#include "../include/configs.h"

void gameState::setBackground()
{
    std::string path = std::string("./assets/backgrounds/") + backgroundPath;
    backgroundTexture.loadFromFile(path);
    backgroundSprite.setTexture(backgroundTexture);
    //backgroundSprite.setScale(WINDOW_WIDTH/backgroundTexture.getSize().x,WINDOW_HEIGHT/backgroundTexture.getSize().y);
}

void gameState::setNumOfGems(int numOfCollectedGems)
{
    numOfGems = numOfCollectedGems;
}
void gameState::setNumOfStar(int numOfCollectedStars)
{
    numOfStars = numOfCollectedStars;
}