#pragma once
//#include "forms.hpp"
#include "miscellaneous.hpp"
#include "gameObject.hpp"
#include <tyra>

struct Cursor{
   //Tyra::Sprite sprite;
   GameObject gameObject;
   Box_collider collider[2];
   bool isMove;                   // Verifica si se movio el jugador
   bool isCenter;                 // Verifica si esta en el centro del cuadrado del jardin
   int deckPosX;                  // Posicion X del mapa o del deck
   int deckPosY;                  // Posicion Y del mapa o del deck
   Tyra::Vec2 offset;
   Tyra::Vec2 center;
};           