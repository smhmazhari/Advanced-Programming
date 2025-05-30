#include "../include/Objects.hpp"
Objects::Objects(int _x, int _y, string image) : x(_x), y(_y)
{
    if (!texture.loadFromFile(image))
        abort();
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    drawn_object = true;
}

void Objects::draw(RenderWindow &window)
{
    if (drawn_object)
        window.draw(sprite);
}
