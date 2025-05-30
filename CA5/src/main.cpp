#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include "Player.hpp"
#include "Objects.hpp"
#include "Game.hpp"
using namespace sf;
using namespace std;

int main()
{
    while (true)
    {
        Game *game = new Game();
        game->set_map("./map/map1.csv");
        if (game->run(*game))
        {
            delete game;
            break;
        }
        delete game;
    }
    return 0;
}