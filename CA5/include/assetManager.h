#ifndef TX_ASSET_MANAGER

#define TX_ASSET_MANAGER

#include "states/playState.h"

class assetManager{

private:

std::map<std::string,sf::Texture> mTexture;

static assetManager* sInstance;

public:

assetManager();

static sf::Texture& getTexture(std::string const&);


};


#endif