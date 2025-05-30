#ifndef TX_CONFIGS_GUARD

#define TX_CONFIGS_GUARD

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

#define TX_WINDOW_WIDTH 1024
#define TX_WINDOW_HEIGHT 768
#define TX_WINDOW_TITLE "Turtix"
#define TX_STATE_NUMBER 9
#define TX_STATE_BACKGROUNDPATH "../assets/backgrounds/"
#define MAINMENUOPTIONNUMBER 3
#define MAINMENUFONT "Roboto-Medium.ttf"
#define NUMOFOPTION 3
const int TOUCH_CILLING_FALL = 3;
const int BLUE_ENEMY_LIVE_WITHOUT_SHIELD = 1;
const int BLOCK_BOUND1 = 1;
const int BLOCK_BOUND2 = 10;
const int GAP = 10;
const int FRAME_RATE = 60;
const int BOUND_LEFT_WALL1 = 8;
const int BOUND_LEFT_WALL2 = 21;
const int BOUND_RIGHT_WALL1 = 7;
const int STEP_SIZE = 6;
const int PLAYER_SPEED = 7;
const int BASE_ENEMY_SPEED = 2;
const int TURTLE_SPEED = 3;
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 800;
const int PORTAL_X = 3865;
const int PORTAL_Y = 710;
const int ENEMY_BECOME_GHOST_TIME = 3;
const int CHANGE_FRAME_TIME = 50;
const int SCORE_FONT_SIZE = 70;
const int NUMBER_OF_HEARTS = 5;
const float GRAVITY = 0.2;
const float JUMP_FIRST_AMOUNT = -11;
#define left isKeyPressed(Keyboard::Left)
#define right isKeyPressed(Keyboard::Right)
#define up isKeyPressed(Keyboard::Up)
const float HIT_JUMP = -7;
const int OBJECT_TYPE_PLACE = 0;
const char SEPERATOR = ',';
const int BLUE_ENEMY_LIVES = 2;
const int ORANGE_ENEMY_LIVES = 1;
const int X_VALUE = 0;
const int Y_VALUE = 1;
const int OBJECT_VALUE = 2;

#endif