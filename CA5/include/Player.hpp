#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
using namespace sf;
using namespace std;
enum Direction
{
    LEFT,
    RIGHT,
    UP,
    NO_WHERE
};

class Player
{
private:
    vector<Texture *> textures;
    Sprite sprite;
    Direction my_direction;
    int x;
    int y;
    int speed;
    int lives;
    int stars;
    int gems;
    int step;
    float dy;
    bool draw_player;
    bool free;
    bool animation;

public:
    Player(int _x, int _y, int new_speed, vector<string> images, bool new_flag);

    void draw(RenderWindow &window);
    void move(Direction direction);
    bool is_draw();
    void do_draw_player(bool mode);
    void make_free_or_not(bool mode);
    void move_to_portal(int _x, int _y);
    void init_num_of_lives(int number);
    void increase_step();

    FloatRect getGlobalBounds() { return sprite.getGlobalBounds(); };
    Vector2u get_size() { return textures[0]->getSize(); };
    Vector2f get_position() { return sprite.getPosition(); };
    Direction get_my_direction() { return my_direction; };

    bool is_free() { return free; };
    int get_lives() { return lives; };
    int get_speed() { return speed; };
    int get_num_of_stars() { return stars; };
    int get_num_of_gems() { return gems; };

    void change_my_direction(Direction new_direction) { my_direction = new_direction; };
    void decrease_num_of_lives() { lives--; };
    void increase_stars() { stars++; };
    void increase_gems() { gems++; };
    void set_gravity(float number) { dy += number; };
    void change_jump_height(float number) { dy = number; };
    void init_scores() { gems = stars = 0; };
    void change_picture(Texture &texture) { sprite.setTexture(texture); };
};