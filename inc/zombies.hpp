#pragma once
#include "plants.hpp"

struct Zombies{
   Plants body;
} ;     

struct Sol{
   Rectangle rec;           // Posicion
   //GUAnimator anim;         // Animacion
   int anim_idle;           // Animacion inicial
   int limitY;              // Limite de caida del sol
   int soles;               // Cantidad de soles que entrega
   bool trigger;            // Choque entre el cursor y el sol
}; 