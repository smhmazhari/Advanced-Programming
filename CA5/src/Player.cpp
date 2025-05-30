#pragma once
#include"../include/Player.hpp"
int delta_x[3] = {-1 , 1 , 0};
Player::Player(int _x, int _y , int new_speed , vector<string> images , bool new_flag) : x(_x), y(_y), speed(new_speed) 
{
    textures.clear();
    for (int i = 0; i < images.size(); i++)
    {
        textures.push_back(new Texture);
        if (!textures[i]->loadFromFile("./pictures/"+images[i]+".png"))
            abort();
    }
    sprite.setTexture(*textures[0]);
    sprite.setPosition(x, y);
    dy = 0;
    draw_player = true;
    free = false;
    my_direction = LEFT;
    lives = 2;
    stars = 0;
    gems = 0;
    step = 1;
    animation = new_flag;
}

void Player::draw(RenderWindow &window)
{
    if (draw_player)
        window.draw(sprite);
    else if (lives <= 0)
    {
        change_picture(*textures[5+my_direction]);
        sprite.setPosition(x,y+18);
    }
    else 
        return;
    window.draw(sprite);
}

void Player::move(Direction direction)
{   int index = 1;
    if (animation)
    {
        if (step > (textures.size()-1)/2)
            step = 1;
        if (direction != UP)
            change_picture(*textures[direction*(textures.size()-1)/2 + step]);
    }
    else
    {
        if (lives == 1)
            index = 3;
        else 
            (index = 1);
        if (direction != UP)
            change_picture(*textures[direction+index]);
    }
    int new_x = x + delta_x[direction] * speed;
    int new_y = y;
    if (direction == UP)
        new_y += dy;
    
    x = new_x;
    y = new_y;
    sprite.setPosition(x, y);
}

bool Player::is_draw()
{
    if (lives <= 0)
        draw_player = false;
    return draw_player;
}

void Player::do_draw_player(bool mode)
{
    draw_player = mode;
}

void Player::make_free_or_not(bool mode)
{
    free = mode;
}
void Player::move_to_portal(int _x , int _y)
{
    x = _x;
    y = _y;
    sprite.setPosition(x,y);
}

void Player::init_num_of_lives(int number)
{
    lives = number;
}

void Player::increase_step()
{
    if (dy == 0)
        step++;
}
