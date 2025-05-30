#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
using namespace std;

class Objects
{
private:
    Texture texture;
    Sprite sprite;
    bool drawn_object;
    int x;
    int y;

public:
    Objects(int _x, int _y, string image);

    void draw(RenderWindow &window);
    void set_position(int _x, int _y) { sprite.setPosition(_x, _y); };
    void do_draw_object(bool draw_or_not) { drawn_object = draw_or_not; };
    bool is_drawn() { return drawn_object; };

    Vector2u get_size() { return texture.getSize(); };
    Vector2f get_position() { return sprite.getPosition(); };
    FloatRect getGlobalBounds() { return sprite.getGlobalBounds(); };
};