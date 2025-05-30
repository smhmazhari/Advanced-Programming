#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include "Player.hpp"
#include "Objects.hpp"
#include "configs.h"
#include <array>
#include "./states/gameState.h"
#include "./states/mainMenuState.h"

typedef std::array<gameState *, TX_STATE_NUMBER> statesList;

class Game
{
private:
    bool started;
    Player player;
    Objects background;
    bool closed;

    vector<Objects *> gates;
    vector<Objects *> blocks;
    vector<Objects *> stars;
    vector<Objects *> gems;
    vector<Objects *> hearts;
    vector<Objects *> thorns;

    vector<Player *> baby_turtles;
    vector<Player *> orange_enemies;
    vector<Player *> blue_enemies;

    Font font;
    Text star_text;
    Text gem_text;

    // statr vector
    statesList states;

    // current state
    gameState *currentState;

    sf::Event event;

public:
    Game();
    bool run(Game &game);
    vector<string> read_map(string line_of_file, char separator);
    void init_game_stuff();
    void init_hearts();
    void make_map(string object, vector<string> map_info);
    void set_map(string address);
    void set_details_position(View &View);
    void set_hearts_position();
    void set_gems_position();
    void set_stars_position();
    void start();

    void draw(RenderWindow &window, View &view, Game &game);
    void draw_blocks(RenderWindow &window);
    void draw_gates(RenderWindow &window);
    void draw_thorns(RenderWindow &window);
    void draw_baby_turtles(RenderWindow &window);
    void draw_orange_enemies(RenderWindow &window);
    void draw_blue_enemies(RenderWindow &window);
    void draw_stars(RenderWindow &window);
    void draw_gems(RenderWindow &window);
    void draw_hearts(RenderWindow &window);

    void transfer_player(Direction direction);
    bool can_move_right(vector<Objects *> &walls, int which_wall);
    bool can_move_left(vector<Objects *> &walls, int which_wall);

    bool can_enemy_move_right(vector<Objects *> &blocks, int which_block, Direction direction, Player object);
    bool can_enemy_move_left(vector<Objects *> &blocks, int which_block, Direction direction, Player object);

    void make_turtles_free();
    void move_baby_turtles();
    void turtles_get_home();
    bool can_turtle_be_free(int which_turtle);
    bool can_baby_turtle_move_right(int which_turtle, vector<Player *> &baby_turtles);
    bool can_baby_turtle_move_left(int which_turtle, vector<Player *> &baby_turtles);

    void touch_thorns();
    bool touch_thorn_happend(int which_thorn);
    bool able_to_do_next_move(vector<Objects *> &walls, Direction direction);
    void move_player(Direction direction);
    void handle_events(RenderWindow &window, Game &game);
    bool can_jump(Player object);
    bool able_to_jump(vector<Objects *> &blocks, int which_block, Player &object);
    void jump(Player &object, bool flag);
    void change_step();
    bool are_blocks_ok_to_jump(vector<Objects *> &blocks, int which_block, Player player);

    void increase_score();
    bool check_we_lost();
    bool check_we_won();

    bool is_enemy_annoying(vector<Player *> &enemies, Direction direction);
    void touch_enemies(vector<Player *> &enemies);
    void kill_enemies(vector<Player *> &enemies);
    void move_enemies(vector<Player *> &enemies);
    void change_blue_enemy_mode();
    void handle_enemies();
    bool touch_enemy_happend(vector<Player *> &enemies, int which_enemy);
    void touch_and_die(vector<Player *> &enemies);
    void touch_and_hit(vector<Player *> &enemies);
    bool is_enemy_hit(vector<Player *> &enemies, int which_enemy);
    bool any_enemy_left(int which_enemy, vector<Player *> &enemies);
    bool any_enemy_right(int which_enemy, vector<Player *> &enemies);

    gameState *noname();
    void menu(sf::RenderWindow &Window);
    void initialGameStates();
    bool isClosed();
};
