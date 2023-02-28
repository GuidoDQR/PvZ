#pragma once
#include <tyra>
#include "Camera.hpp"
#include "textures.hpp"
#include "gameObject.hpp"


extern Tyra::Sprite spr_box_collider;

bool Load_sprite_box_collider(Tyra::Engine* engine);
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

    Box_collider box;
    public:
    Map();
    GameObject gameObject;
    Tyra::Sprite* collider;
    Tyra::Vec2 center;
};