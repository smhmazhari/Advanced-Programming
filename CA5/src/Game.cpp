#include "../include/states/gameState.h"
#include "../include/states/mainMenuState.h"
#include "../include/states/winState.h"
#include "../include/states/loseState.h"
#include "../include/states/puaseState.h"
#include "../include/configs.h"
#include "../include/Player.hpp"
#include "../include/Objects.hpp"
#include "../include/Game.hpp"

using namespace std;
vector<string> player_images = {"player1", "player1", "player2", "player3", "player4", "player5", "player6", "player7", "player8", "player9",
                                "player10", "player11", "player12", "player13", "player14", "player15", "player16", "player17", "player18"};
vector<string> baby_turtle_images = {"turtle_in_bubble", "turtle1", "turtle2", "turtle3", "turtle4", "turtle5", "turtle6", "turtle7", "turtle8",
                                     "turtle9", "turtle10", "turtle11", "turtle12", "turtle13", "turtle14", "turtle15", "turtle16"};
vector<string> weak_enemy_images = {"weak_enemy1", "weak_enemy1", "weak_enemy2", "weak_enemy3", "weak_enemy4", "weak_enemy5", "weak_enemy6"};
vector<string> strong_enemy_images = {"strong_enemy1", "strong_enemy1", "strong_enemy2", "strong_enemy3", "strong_enemy4", "strong_enemy5", "strong_enemy6"};

Game::Game() : player(PORTAL_X, PORTAL_Y, PLAYER_SPEED, player_images, true), background(0, 0, "./pictures/back1.jpg")
{
    font.loadFromFile("font/arialbd.ttf");
    star_text.setFont(font);
    star_text.setCharacterSize(SCORE_FONT_SIZE);
    star_text.setFillColor(Color::Black);
    gem_text.setFont(font);
    gem_text.setCharacterSize(SCORE_FONT_SIZE);
    gem_text.setFillColor(Color::Black);
}

bool Game::run(Game &game)
{
    RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Turtix");
    bool flag = false;
    game.initialGameStates();
    game.menu(window);
    if (states[_exit])
    {
        return true;
    }
    View view(FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
    window.setFramerateLimit(FRAME_RATE);
    window.setView(view);
    Clock clock_ghost_time;
    Clock change_frame_time;

    while (window.isOpen())
    {
        Time enemy_become_ghost = clock_ghost_time.getElapsedTime();
        Time elapsed_time = change_frame_time.getElapsedTime();
        if (game.check_we_lost())
        {
            states[_loseState] = new loseState();
            currentState = states[_loseState];

            delete states[_playState];
            states[_playState] = nullptr;

            window.close();
            RenderWindow newWin(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "LOSE");
            game.menu(newWin);
            return false;
        }
        else if (game.check_we_won())
        {
            states[_winState] = new winState();
            currentState = states[_winState];

            delete states[_playState];
            states[_playState] = nullptr;

            window.close();
            RenderWindow newWin(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "WIN");
            game.menu(newWin);
            return false;
        }
        if (enemy_become_ghost.asSeconds() >= ENEMY_BECOME_GHOST_TIME)
        {
            game.change_blue_enemy_mode();
            clock_ghost_time.restart();
        }
        if (elapsed_time.asMilliseconds() >= CHANGE_FRAME_TIME)
        {
            game.change_step();
            change_frame_time.restart();
        }
        game.handle_events(window, game);
        game.move_baby_turtles(); /*l*/
        game.turtles_get_home();
        game.increase_score();
        game.handle_enemies();
        game.draw(window, view, game);
        window.display();
    }
    return false;
}
vector<string> Game::read_map(string line_of_file, char separator)
{
    string file_element;
    vector<string> inputs;
    istringstream line(line_of_file);
    while (getline(line, file_element, separator))
    {
        inputs.push_back(file_element);
    }
    return inputs;
}

void Game::init_game_stuff()
{
    player.move_to_portal(PORTAL_X, PORTAL_Y);
    player.init_scores();
    player.init_num_of_lives(NUMBER_OF_HEARTS);
    started = true;
    blocks.clear();
    thorns.clear();
    baby_turtles.clear();
    gates.clear();
    orange_enemies.clear();
    blue_enemies.clear();
    gems.clear();
    stars.clear();
    hearts.clear();
    init_hearts();
}
void Game::init_hearts()
{
    for (int dead_heart = 0; dead_heart < NUMBER_OF_HEARTS; dead_heart++)
        hearts.push_back(new Objects(0, 0, "./pictures/dead_heart.png"));
    for (int left_heart = 0; left_heart < NUMBER_OF_HEARTS; left_heart++)
        hearts.push_back(new Objects(0, 0, "./pictures/heart.png"));
}
void Game::make_map(string object, vector<string> map_info)
{
    if (object == "blocks")
        blocks.push_back(new Objects(stoi(map_info[X_VALUE]), stoi(map_info[Y_VALUE]), "./pictures/" + map_info[OBJECT_VALUE] + ".png"));
    else if (object == "thorns")
        thorns.push_back(new Objects(stoi(map_info[X_VALUE]), stoi(map_info[Y_VALUE]), "./pictures/" + map_info[OBJECT_VALUE] + ".png"));
    else if (object == "turtles")
        baby_turtles.push_back(new Player(stoi(map_info[X_VALUE]), stoi(map_info[Y_VALUE]), TURTLE_SPEED, baby_turtle_images, true));
    else if (object == "gates")
        gates.push_back(new Objects(stoi(map_info[X_VALUE]), stoi(map_info[Y_VALUE]), "./pictures/" + map_info[OBJECT_VALUE] + ".png"));
    else if (object == "weak_enemies")
        orange_enemies.push_back(new Player(stoi(map_info[X_VALUE]), stoi(map_info[Y_VALUE]), BASE_ENEMY_SPEED + stoi(map_info[OBJECT_VALUE]), weak_enemy_images, false));
    else if (object == "strong_enemies")
        blue_enemies.push_back(new Player(stoi(map_info[X_VALUE]), stoi(map_info[Y_VALUE]), BASE_ENEMY_SPEED + stoi(map_info[OBJECT_VALUE]), strong_enemy_images, false));
    else if (object == "gems")
        gems.push_back(new Objects(stoi(map_info[X_VALUE]), stoi(map_info[Y_VALUE]), "./pictures/blue4.gif"));
    else if (object == "stars")
        stars.push_back(new Objects(stoi(map_info[X_VALUE]), stoi(map_info[Y_VALUE]), "./pictures/shining_star.gif")); /*map_info[OBJECT_VALUE] */
    else
        return;
}

void Game::set_map(string address)
{
    string object_type;
    string line_of_file;
    vector<string> map_info;
    ifstream map_file(address);
    init_game_stuff();
    while (getline(map_file, line_of_file))
    {
        map_info = read_map(line_of_file, SEPERATOR);

        if (map_info[OBJECT_TYPE_PLACE] == "blocks")
            object_type = "blocks";
        else if (map_info[OBJECT_TYPE_PLACE] == "thorns")
            object_type = "thorns";
        else if (map_info[OBJECT_TYPE_PLACE] == "turtles")
            object_type = "turtles";
        else if (map_info[OBJECT_TYPE_PLACE] == "gates")
            object_type = "gates";
        else if (map_info[OBJECT_TYPE_PLACE] == "weak_enemies")
            object_type = "weak_enemies";
        else if (map_info[OBJECT_TYPE_PLACE] == "strong_enemies")
            object_type = "strong_enemies";
        else if (map_info[OBJECT_TYPE_PLACE] == "gems")
            object_type = "gems";
        else if (map_info[OBJECT_TYPE_PLACE] == "stars")
            object_type = "stars";
        else
            make_map(object_type, map_info);
    }
    map_file.close();
}

void Game::set_details_position(View &view)
{

    background.set_position(view.getCenter().x - WINDOW_WIDTH / 2, view.getCenter().y - WINDOW_HEIGHT / 2);
    set_stars_position();
    set_gems_position();
    set_hearts_position();
}
void Game::set_gems_position()
{
    gems[0]->set_position(background.get_position().x + 1500, background.get_position().y + 140);
    gem_text.setPosition(background.get_position().x + 1420, background.get_position().y + 130);
    gem_text.setString(to_string(player.get_num_of_gems()));
}
void Game::set_stars_position()
{
    stars[0]->set_position(background.get_position().x + 1500, background.get_position().y + 220);
    star_text.setPosition(background.get_position().x + 1420, background.get_position().y + 220);
    if (player.get_num_of_stars() >= 10)
        star_text.setPosition(background.get_position().x + 1420, background.get_position().y + 220);
    star_text.setString(to_string(player.get_num_of_stars()));
}
void Game::set_hearts_position()
{
    int new_x = background.get_position().x + 1500;
    int new_y = background.get_position().y + 50;
    for (int which_heart = 0; which_heart < NUMBER_OF_HEARTS; which_heart++)
    {
        hearts[which_heart]->set_position(new_x - which_heart * 100, new_y);
        hearts[which_heart + NUMBER_OF_HEARTS]->set_position(new_x - which_heart * 100, new_y);
    }
}

void Game::draw(RenderWindow &window, View &view, Game &game)
{
    window.clear();

    set_details_position(view);
    background.draw(window);

    game.draw_blocks(window);
    game.draw_baby_turtles(window);
    game.draw_blue_enemies(window);
    game.draw_gates(window);
    game.draw_gems(window);
    game.draw_hearts(window);
    game.draw_orange_enemies(window);
    game.draw_stars(window);
    game.draw_thorns(window);

    window.draw(star_text);
    window.draw(gem_text);
    player.draw(window);
    view.setCenter(player.get_position().x, player.get_position().y + 100);
    window.setView(view);
}
bool Game::can_move_right(vector<Objects *> &object, int which_object)
{
    return (object[which_object]->getGlobalBounds().intersects(player.getGlobalBounds()) &&
            player.get_position().x + player.get_size().x - STEP_SIZE <=
                object[which_object]->get_position().x);
}
bool Game::can_move_left(vector<Objects *> &object, int which_object)
{
    return (object[which_object]->getGlobalBounds().intersects(player.getGlobalBounds()) &&
            player.get_position().x >= object[which_object]->get_position().x +
                                           object[which_object]->get_size().x - STEP_SIZE);
}

bool Game::able_to_do_next_move(vector<Objects *> &walls, Direction direction)
{
    for (int which_wall = 0; which_wall < walls.size(); which_wall++)
    {
        if (which_wall == BOUND_RIGHT_WALL1 && direction == RIGHT && player.get_position().y <= walls[which_wall]->get_position().y)
            continue;
        if ((which_wall == BOUND_LEFT_WALL1 || which_wall == BOUND_LEFT_WALL2) && direction == LEFT)
            continue;

        if (walls[which_wall]->getGlobalBounds().intersects(player.getGlobalBounds()) &&
            player.get_position().x + player.get_size().x - STEP_SIZE <=
                walls[which_wall]->get_position().x &&
            direction == RIGHT)
            return false;
        if ((walls[which_wall]->getGlobalBounds().intersects(player.getGlobalBounds()) &&
             player.get_position().x >= walls[which_wall]->get_position().x +
                                            walls[which_wall]->get_size().x - STEP_SIZE) &&
            direction == LEFT)
            return false;
    }
    return true;
}
bool Game::any_enemy_left(int which_enemy, vector<Player *> &enemies)
{
    return (enemies[which_enemy]->getGlobalBounds().intersects(player.getGlobalBounds()) &&
            player.get_position().x >= enemies[which_enemy]->get_position().x +
                                           enemies[which_enemy]->get_size().x - STEP_SIZE - enemies[which_enemy]->get_speed());
}
bool Game::any_enemy_right(int which_enemy, vector<Player *> &enemies)
{
    return (enemies[which_enemy]->getGlobalBounds().intersects(player.getGlobalBounds()) &&
            player.get_position().x + player.get_size().x - STEP_SIZE -
                    enemies[which_enemy]->get_speed() <=
                enemies[which_enemy]->get_position().x);
}
bool Game::is_enemy_annoying(vector<Player *> &enemies, Direction direction)
{
    for (int which_enemy = 0; which_enemy < enemies.size(); which_enemy++)
    {
        if (!enemies[which_enemy]->is_draw())
            continue;
        if ((direction == LEFT && any_enemy_left(which_enemy, enemies)) ||
            (direction == RIGHT && any_enemy_right(which_enemy, enemies)))
        {
            player.move_to_portal(PORTAL_X, PORTAL_Y);
            player.decrease_num_of_lives();
            return true;
        }
    }
    return false;
}
bool Game::can_baby_turtle_move_right(int which_turtle, vector<Player *> &baby_turtles)
{
    return (baby_turtles[which_turtle]->getGlobalBounds().intersects(player.getGlobalBounds()) && player.get_position().x <= baby_turtles[which_turtle]->get_position().x && !baby_turtles[which_turtle]->is_free());
}
bool Game::can_baby_turtle_move_left(int which_turtle, vector<Player *> &baby_turtles)
{
    return (baby_turtles[which_turtle]->getGlobalBounds().intersects(player.getGlobalBounds()) && player.get_position().x >= baby_turtles[which_turtle]->get_position().x && !baby_turtles[which_turtle]->is_free());
}
void Game::move_player(Direction direction)
{
    if (!started)
        return;
    if (!able_to_do_next_move(blocks, direction))
        return;
    if (is_enemy_annoying(orange_enemies, direction))
        return;
    if (is_enemy_annoying(blue_enemies, direction))
        return;
    for (int which_turtle = 0; which_turtle < baby_turtles.size(); which_turtle++)
    {

        if (direction == LEFT && can_baby_turtle_move_left(which_turtle, baby_turtles))
            return;
        else if (direction == RIGHT && can_baby_turtle_move_right(which_turtle, baby_turtles))
            return;
    }
    player.move(direction);
}

void Game::handle_events(RenderWindow &window, Game &game)
{
    Event event;
    transfer_player(NO_WHERE);
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
            window.close();

        else if (event.KeyPressed)
        {
            switch (event.key.code)
            {
            case Keyboard::Escape:
            {
                window.close();
                break;
            }
            case Keyboard::Left:
            {
                transfer_player(LEFT);
                break;
            }
            case Keyboard::Right:
            {
                transfer_player(RIGHT);
                break;
            }
            case Keyboard::Up:
            {
                transfer_player(UP);
                break;
            }
            case Keyboard::P:
            {
                delete states[_playState];
                states[_playState] = nullptr;
                states[_pauseState] = new pauseState();
                currentState = states[_pauseState];
                //RenderWindow newWin(VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT ), "Turtix");
                game.menu(window);
                //newWin.close();
            }
            }
        }
    }
}
bool Game::are_blocks_ok_to_jump(vector<Objects *> &blocks, int which_block, Player object)
{
    return (blocks[which_block]->getGlobalBounds().intersects(object.getGlobalBounds()) &&
            object.get_position().y <= blocks[which_block]->get_position().y &&
            object.get_position().x + object.get_size().x - GAP >= blocks[which_block]->get_position().x &&
            object.get_position().x <= blocks[which_block]->get_position().x + blocks[which_block]->get_size().x - GAP);
}
bool Game::can_jump(Player object)
{
    for (int which_block = 0; which_block < blocks.size(); which_block++)
    {
        if (are_blocks_ok_to_jump(blocks, which_block, object))
            return true;
    }
    return false;
}
bool Game::able_to_jump(vector<Objects *> &blocks, int which_block, Player &object)
{
    return (blocks[which_block]->getGlobalBounds().intersects(object.getGlobalBounds()) &&
            object.get_position().y >= blocks[which_block]->get_position().y + blocks[which_block]->get_size().y / 2 &&
            object.get_position().x + object.get_size().x >= blocks[which_block]->get_position().x + PLAYER_SPEED + 1 &&
            object.get_position().x + PLAYER_SPEED + 1 <= blocks[which_block]->get_position().x + blocks[which_block]->get_size().x);
}
void Game::jump(Player &object, bool jump_or_not)
{
    if (!started)
        return;
    else if (!can_jump(object))
        object.set_gravity(GRAVITY);
    else if (Keyboard::isKeyPressed(Keyboard::Up) && jump_or_not)
        object.change_jump_height(JUMP_FIRST_AMOUNT);
    else
        object.change_jump_height(0);

    for (int which_block = 0; which_block < blocks.size(); which_block++)
    {
        if (which_block == BLOCK_BOUND1 || which_block == BLOCK_BOUND2)
            continue;
        if (able_to_jump(blocks, which_block, object))
            object.change_jump_height(TOUCH_CILLING_FALL);
    }
    if (jump_or_not)
        move_player(UP);
    else
        object.move(UP);
}

void Game::draw_blocks(RenderWindow &window)
{
    for (int which_block = 0; which_block < blocks.size(); which_block++)
        blocks[which_block]->draw(window);
}
void Game::draw_gates(RenderWindow &window)
{
    for (int which_gate = 0; which_gate < gates.size(); which_gate++)
        gates[which_gate]->draw(window);
}
void Game::draw_thorns(RenderWindow &window)
{
    for (int which_thorn = 0; which_thorn < thorns.size(); which_thorn++)
        thorns[which_thorn]->draw(window);
}
void Game::draw_baby_turtles(RenderWindow &window)
{
    for (int which_turtle = 0; which_turtle < baby_turtles.size(); which_turtle++)
        baby_turtles[which_turtle]->draw(window);
}
void Game::draw_orange_enemies(RenderWindow &window)
{
    for (int which_orange_enemy = 0; which_orange_enemy < orange_enemies.size(); which_orange_enemy++)
        orange_enemies[which_orange_enemy]->draw(window);
}
void Game::draw_blue_enemies(RenderWindow &window)
{
    for (int which_blue_enemy = 0; which_blue_enemy < blue_enemies.size(); which_blue_enemy++)
        blue_enemies[which_blue_enemy]->draw(window);
}
void Game::draw_stars(RenderWindow &window)
{
    for (int which_star = 0; which_star < stars.size(); which_star++)
        stars[which_star]->draw(window);
}
void Game::draw_gems(RenderWindow &window)
{
    for (int which_gem = 0; which_gem < gems.size(); which_gem++)
        gems[which_gem]->draw(window);
}
void Game::draw_hearts(RenderWindow &window)
{
    for (int which_heart = 0; which_heart < NUMBER_OF_HEARTS + player.get_lives(); which_heart++)
        hearts[which_heart]->draw(window);
}
void Game::start()
{
    started = true;
}

void Game::transfer_player(Direction direction)
{
    if (direction == NO_WHERE)
    {
        if (Keyboard::left)
            move_player(LEFT);
        else if (Keyboard::right)
            move_player(RIGHT);
        jump(player, true);
    }
}

bool Game::can_turtle_be_free(int which_turtle)
{
    return (baby_turtles[which_turtle]->getGlobalBounds().intersects(player.getGlobalBounds()) && player.get_position().y <= baby_turtles[which_turtle]->get_position().y && player.get_position().x + player.get_size().x - 5 >= baby_turtles[which_turtle]->get_position().x && player.get_position().x <= baby_turtles[which_turtle]->get_position().x + baby_turtles[which_turtle]->get_size().x - 5);
}
void Game::make_turtles_free()
{
    for (int which_baby_turtle = 0; which_baby_turtle < baby_turtles.size(); which_baby_turtle++)
    {
        if (baby_turtles[which_baby_turtle]->is_free())
            continue;
        if (can_turtle_be_free(which_baby_turtle))
        {
            baby_turtles[which_baby_turtle]->make_free_or_not(true);
            player.change_jump_height(HIT_JUMP);
            move_player(UP);
        }
    }
}
void Game::move_baby_turtles()
{
    make_turtles_free();
    for (int which_baby_turtle = 0; which_baby_turtle < baby_turtles.size(); which_baby_turtle++)
    {
        Player object = *baby_turtles[which_baby_turtle];
        Direction direction = object.get_my_direction();
        if (!baby_turtles[which_baby_turtle]->is_free() || !baby_turtles[which_baby_turtle]->is_draw())
            continue;
        jump(*baby_turtles[which_baby_turtle], false);
        for (int which_block = 0; which_block < blocks.size(); which_block++)
        {
            if (direction == LEFT && (which_block == BOUND_LEFT_WALL1 || which_block == BOUND_LEFT_WALL2))
                continue;
            if (direction == RIGHT && which_block == BOUND_RIGHT_WALL1 & object.get_position().y <= blocks[which_block]->get_position().y)
                continue;
            if (direction == LEFT && blocks[which_block]->getGlobalBounds().intersects(object.getGlobalBounds()) &&
                object.get_position().x >= blocks[which_block]->get_position().x + blocks[which_block]->get_size().x - STEP_SIZE)
            {
                direction = RIGHT;
                break;
            }
            else if (direction == RIGHT && blocks[which_block]->getGlobalBounds().intersects(object.getGlobalBounds()) &&
                     object.get_position().x + object.get_size().x - STEP_SIZE <= blocks[which_block]->get_position().x)
            {
                direction = LEFT;
                break;
            }
        }
        baby_turtles[which_baby_turtle]->change_my_direction(direction);
        baby_turtles[which_baby_turtle]->move(direction);
    }
}
void Game::turtles_get_home()
{
    for (int which_baby_turtle = 0; which_baby_turtle < baby_turtles.size(); which_baby_turtle++)
        if (gates[0]->getGlobalBounds().intersects(baby_turtles[which_baby_turtle]->getGlobalBounds()))
            baby_turtles[which_baby_turtle]->do_draw_player(false);
}
bool Game::touch_thorn_happend(int which_thorn)
{
    return (thorns[which_thorn]->getGlobalBounds().intersects(player.getGlobalBounds()) &&
            player.get_position().y + player.get_size().y >= thorns[which_thorn]->get_position().y + 25 &&
            player.get_position().x + player.get_size().x >= thorns[which_thorn]->get_position().x + 20 &&
            player.get_position().x + 20 <= thorns[which_thorn]->get_position().x + thorns[which_thorn]->get_size().x);
}
void Game::touch_thorns()
{
    for (int which_thorn = 0; which_thorn < thorns.size(); which_thorn++)
    {
        if (touch_thorn_happend(which_thorn))
        {
            player.move_to_portal(PORTAL_X, PORTAL_Y);
            player.decrease_num_of_lives();
        }
    }
}
bool Game::touch_enemy_happend(vector<Player *> &enemies, int which_enemy)
{
    return (enemies[which_enemy]->getGlobalBounds().intersects(player.getGlobalBounds()) && player.get_position().y <= enemies[which_enemy]->get_position().y + 3 * enemies[which_enemy]->get_size().y / 4 && player.get_position().x + player.get_size().x >= enemies[which_enemy]->get_position().x + 30 && player.get_position().x + 30 <= enemies[which_enemy]->get_position().x + enemies[which_enemy]->get_size().x);
}
void Game::touch_and_die(vector<Player *> &enemies)
{
    for (int which_enemy = 0; which_enemy < enemies.size(); which_enemy++)
    {
        if (!enemies[which_enemy]->is_draw())
            continue;
        if (touch_enemy_happend(enemies, which_enemy))
        {
            player.move_to_portal(PORTAL_X, PORTAL_Y);
            player.decrease_num_of_lives();
            return;
        }
    }
}
void Game::touch_and_hit(vector<Player *> &enemies)
{
    for (int which_enemy = 0; which_enemy < enemies.size(); which_enemy++)
    {
        if (!enemies[which_enemy]->is_draw())
            continue;
        if (enemies[which_enemy]->getGlobalBounds().intersects(player.getGlobalBounds()))
        {
            player.change_jump_height(HIT_JUMP / 2);
            move_player(UP);
        }
    }
}
void Game::touch_enemies(vector<Player *> &enemies)
{
    touch_and_die(enemies);
    touch_and_hit(enemies);
}
bool Game::is_enemy_hit(vector<Player *> &enemies, int which_enemy)
{
    return (enemies[which_enemy]->getGlobalBounds().intersects(player.getGlobalBounds()) &&
            player.get_position().y + 3 * player.get_size().y / 4 <= enemies[which_enemy]->get_position().y &&
            player.get_position().x + player.get_size().x >= enemies[which_enemy]->get_position().x + 11 &&
            player.get_position().x + 11 <= enemies[which_enemy]->get_position().x + enemies[which_enemy]->get_size().x);
};
void Game::kill_enemies(vector<Player *> &enemies)
{
    for (int which_enemy = 0; which_enemy < enemies.size(); which_enemy++)
    {
        if (!enemies[which_enemy]->is_draw() || !started)
            continue;
        if (is_enemy_hit(enemies, which_enemy))
        {
            enemies[which_enemy]->decrease_num_of_lives();
            if (enemies[which_enemy]->get_lives() >= 1)
                player.change_jump_height(HIT_JUMP);
            else if (enemies[which_enemy]->get_lives() == 0)
                player.change_jump_height(HIT_JUMP);
            move_player(UP);
        }
    }
}
bool Game::can_enemy_move_left(vector<Objects *> &blocks, int which_block, Direction direction, Player object)
{
    return (direction == LEFT && blocks[which_block]->getGlobalBounds().intersects(object.getGlobalBounds()) && (object.get_position().x >= blocks[which_block]->get_position().x + blocks[which_block]->get_size().x - STEP_SIZE || object.get_position().x <= blocks[which_block]->get_position().x));
}
bool Game::can_enemy_move_right(vector<Objects *> &blocks, int which_block, Direction direction, Player object)
{
    return (direction == RIGHT && blocks[which_block]->getGlobalBounds().intersects(object.getGlobalBounds()) && (object.get_position().x + object.get_size().x - STEP_SIZE <= blocks[which_block]->get_position().x || object.get_position().x + object.get_size().x >= blocks[which_block]->get_position().x + blocks[which_block]->get_size().x));
}
void Game::move_enemies(vector<Player *> &enemies) /*MANDE*/
{
    if (!started)
        return;
    for (int which_enemy = 0; which_enemy < enemies.size(); which_enemy++)
    {
        Player object = *enemies[which_enemy];
        Direction direction = object.get_my_direction();
        if (!enemies[which_enemy]->is_draw())
            continue;
        jump(*enemies[which_enemy], false);
        for (int which_block = 0; which_block < blocks.size(); which_block++)
        {
            if (direction == LEFT && (which_block == BOUND_LEFT_WALL1 || which_block == BOUND_LEFT_WALL2))
                continue;
            if (direction == RIGHT && which_block == BOUND_RIGHT_WALL1 & object.get_position().y <= blocks[which_block]->get_position().y)
                continue;
            if (can_enemy_move_left(blocks, which_block, direction, object))
            {
                direction = RIGHT;
                break;
            }
            else if (can_enemy_move_right(blocks, which_block, direction, object))
            {
                direction = LEFT;
                break;
            }
        }
        enemies[which_enemy]->change_my_direction(direction);
        enemies[which_enemy]->move(direction);
    }
}

void Game::change_blue_enemy_mode()
{
    for (int which_blue_enemy = 0; which_blue_enemy < blue_enemies.size(); which_blue_enemy++)
    {
        if (blue_enemies[which_blue_enemy]->get_lives() == BLUE_ENEMY_LIVE_WITHOUT_SHIELD)
            blue_enemies[which_blue_enemy]->init_num_of_lives(BLUE_ENEMY_LIVES);
        else if (blue_enemies[which_blue_enemy]->get_lives() == BLUE_ENEMY_LIVES)
            blue_enemies[which_blue_enemy]->init_num_of_lives(BLUE_ENEMY_LIVE_WITHOUT_SHIELD);
    }
}

void Game::handle_enemies()
{
    bool enemy_shield = false;
    touch_thorns();
    move_enemies(orange_enemies);
    kill_enemies(orange_enemies);
    touch_enemies(orange_enemies);
    move_enemies(blue_enemies);
    for (int which_blue_enemy = 0; which_blue_enemy < blue_enemies.size(); which_blue_enemy++)
        if (blue_enemies[which_blue_enemy]->get_lives() == BLUE_ENEMY_LIVES)
            enemy_shield = true;
    if (!enemy_shield)
        kill_enemies(blue_enemies);
    touch_enemies(blue_enemies);
}

void Game::increase_score()
{
    for (int which_star = 0; which_star < stars.size(); which_star++)
        if (stars[which_star]->getGlobalBounds().intersects(player.getGlobalBounds()) && stars[which_star]->is_drawn())
        {
            stars[which_star]->do_draw_object(false);
            player.increase_stars();
        }
    for (int which_gem = 0; which_gem < gems.size(); which_gem++)
        if (gems[which_gem]->getGlobalBounds().intersects(player.getGlobalBounds()) && gems[which_gem]->is_drawn())
        {
            gems[which_gem]->do_draw_object(false);
            player.increase_gems();
        }
}

void Game::change_step()
{
    player.increase_step();
    for (int which_turtle = 0; which_turtle < baby_turtles.size(); which_turtle++)
        baby_turtles[which_turtle]->increase_step();
}
bool Game::check_we_lost()
{
    return player.get_lives() <= 0;
}
bool Game::check_we_won()
{
    int num_of_saved_turtles = 0;
    for (int which_baby_turtle = 0; which_baby_turtle < baby_turtles.size(); which_baby_turtle++)
        if (!baby_turtles[which_baby_turtle]->is_draw())
            num_of_saved_turtles++;
    return (gates[0]->getGlobalBounds().intersects(player.getGlobalBounds()) && num_of_saved_turtles == baby_turtles.size());
}

void Game::menu(sf::RenderWindow &window)
{
    bool flag = false;
    while (window.isOpen())
    {
        window.setMouseCursorVisible(false);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            window.clear();
            currentState = currentState->eventHandle(window, states, event);
            if (states[_playState])
            {
                flag = true;
                break;
            }
        }
        if (flag)
        {
            break;
        }
        currentState->setNumOfGems(player.get_num_of_gems());
        currentState->setNumOfStar(player.get_num_of_stars());
        currentState = currentState->update(window, states);
        window.clear();
        currentState->render(window);
        window.display();
    }
}

void Game::initialGameStates()
{
    for (int i = 0; i < TX_STATE_NUMBER; i++)
    {
        states[i] = nullptr;
    }
    currentState = nullptr;
    states[_mainMenuState] = new mainMenuState();
    currentState = states[_mainMenuState];
}

bool Game::isClosed()
{
    return closed;
}
