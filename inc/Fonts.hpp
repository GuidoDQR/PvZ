#pragma once

#include <tyra>
#include "main.hpp"
#include "textures.hpp"
#include "string.h"

const float BriannedTod12Width[192]{
    9,  10,  10,   8,   9,   8,  11,   9,   4,   9,  10,   9,  10,   8,   9,   8,
    9,  10,   8,  10,   9,   9,  11,   8,   7,   8,   7,   7,   6,   7,   6,   8,
    7,   7,   4,   6,   8,   3,   9,   8,   7,   6,   7,   7,   6,   7,   7,   6,
    8,   6,   7,   7,   7,   3,   8,   8,   7,   8,   8,   8,   8,   8,   8,   3,
    4,  10,  11,   9,  11,   5,   7,   8,   6,   6,   7,   8,   8,   8,   5,   8,
    5,   8,   4,   4,   3,   5,   4,   8,   4,   8,   4,   6,   3,   6,   9,   7,
    8,   9,   9,   6,   9,   9,   9,   9,   9,   9,  12,  10,  10,  10,  10,  10,
    4,   4,   4,   3,   8,   8,  10,   9,   9,  10,  10,   9,   9,   9,   9,   9,
    7,  10,   8,   8,   8,   8,   8,   8,  10,   9,   6,   6,   6,   6,   4,   4,
    4,   4,   7,   8,   7,   7,   7,   7,   7,   7,   7,   7,   6,   7,   7,   7 
};

bool Load_sprite_text_font(Tyra::Engine* engine);
void DrawText(std::string text, int x, int y);
void ChangeColorFont(Tyra::Color newColor);

extern Tyra::Sprite spr_font_BrianneTod12;
extern Tyra::Sprite spr_textFont[192];