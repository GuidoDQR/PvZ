#pragma once
#include <tyra>
#include "gameObject.hpp"
#include "miscellaneous.hpp"
enum debugoptions{
    null, d_sprite, d_box, d_hidebackground,d_map,d_cursorPlayer1, d_animation,
    d_maxOptions,
    d_firstOption = null+1
};

class DebugBox{
private:
    Box_collider box;
public:
    DebugBox();
    GameObject gameObject;
    Tyra::Sprite* collider;
};

//static DebugBox& globalDebugBox() { static DebugBox x; return x;}

void ShowDebugOptions();
void DebugCrossOptions();
void DebugCircleOptions();

extern int  optiondebug1;
extern int  debug_render_size_map_x;
extern int  debug_render_size_map_y;
extern bool optiondebug2;
extern bool b_debug;
extern bool b_debugSprite;
extern bool b_debugBox;
extern bool b_debugHidebackground;
extern bool b_debugMap;
extern bool b_debugCursorPlayer1;
extern Tyra::Sprite debug_sprite; 
//extern DebugBox* debug_box_col;