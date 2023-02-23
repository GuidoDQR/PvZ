#pragma once

#include "gameObject.hpp"
#include "forms.hpp"
#include "deck.hpp"
   
struct Plants {
   //Rectangle rec;                     // Posicion
   GameObject gameObject;              // Posicion
   //Tyra::Vec2 pos;               // Posicion
   //GUAnimator anim;                   // Animacion
   int life;                          // Vida
   int damage;                        // Daño
   int anim_idle;                     // Animacion inicial
   int cost;                          // Costo de soles
   float chargeTimeMax;        // Tiempo de recarga para poder comprar
   float bulletTimeMax;        // Tiempo de recarga para poder comprar
   float timer;                       // Tiempo faltante para recargar
   float timerBullet;                 // Tiempo faltante para disparar
}; 

struct Lanzaguisantes{
        Plants body;
};  

struct Projectile{
   Rectangle rec;
   //GUAnimator anim;                   // Animacion
   int anim_idle;                     // Animacion inicial
   int damage;                        // Daño
   bool exist;
};  

void generadorDeLanzaguisantes(Lanzaguisantes *plant);         

void plantsInLevel(int stage,int level);
void desbloquearPlanta(int stage, int level);
  