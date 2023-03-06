#pragma once

#include <tyra>
#include <iostream>

enum SpritesTextures { PeaShooterSingle };

extern std::vector<Tyra::Sprite*> spr_PeaShooterSingle;

void LoadSprite (Tyra::Sprite* sprite, Tyra::Vec2 newPos, Tyra::Vec2 newSize, Tyra::SpriteMode mode);
void LoadSprite (Tyra::Sprite* sprite, Tyra::Vec2 newPos, Tyra::Vec2 newSize);
void LoadSprite (Tyra::Sprite* sprite);
void LoadSprite (Tyra::Sprite* sprite, Tyra::Vec2 newPosition);

void LoadTexture(Tyra::Sprite* sprite, const char* image, Tyra::Engine* engine);

void Load_PeaShooter_Single_Sprites(Tyra::Engine* engine);