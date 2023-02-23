#pragma once
#include <tyra>
#include "Camera.hpp"
#include "textures.hpp"
#include "gameObject.hpp"

extern Tyra::Sprite spr_textFont;
extern Tyra::Sprite spr_box_collider;

bool Load_sprite_box_collider(Tyra::Engine* engine);
bool Load_sprite_text_font(Tyra::Engine* engine);
bool ColliderCollision(Tyra::Sprite col1, Tyra::Sprite col2);

//  Color meaning

//  white = collision collider
//  red   = hit collider
//  blue  = health collider
//  green = Trigger collider

class Box_collider{
    public:
    Box_collider();
    //~Box_collider();
    Tyra::Sprite sprite;
};

class Map{

    
    public:
    Map();
    GameObject gameObject;
    Box_collider collider;
    Tyra::Vec2 center;
};