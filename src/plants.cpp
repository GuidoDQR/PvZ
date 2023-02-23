#include "plants.hpp"
#include <stdio.h>

void plantsInDay(int);
void plantsInNight(int);
void plantsInPool(int);
void plantsInFog(int);
void plantsInRoof(int);     

// Tiempos de recarga de las plantas

unsigned int rapida = 5;
unsigned int mediocre = 15;
unsigned int pausada = 20;
unsigned int lenta = 35;
unsigned int muyLenta = 60;

// Tiempo de recarga de la municion

unsigned int bullet_rapida = 1.5;

// Tipos de daños

unsigned int debil = 5;
unsigned int normal = 10;
unsigned int moderado = 15;
unsigned int grande = 20;
unsigned int enorme = 25;
unsigned int masivo = 30;

// Dureza

unsigned int minima = 3;
unsigned int tipica = 5;
unsigned int elevada = 40;
unsigned int alta = 80;
unsigned int muyAlta = 160;

// stage means where is the place of the game
// stage: [day-1] [night-2] [pool-3] [fog-4] [roof-5]
void plantsInLevel(int stage,int level){
     switch(stage){
         case 1:
              plantsInDay(level);
              break;
         case 2:
              plantsInNight(level);
              break;
         case 3:
              plantsInPool(level);
              break;
         case 4:
              plantsInFog(level);
              break;
         case 5:
              plantsInRoof(level);
              break;
     }
}

void plantsInDay(int level){
     switch(level){
         case 1:
              printf("Lanzaguisantes desbloqueada\n");
              break;
     }
}

void plantsInNight(int level){
     switch(level){
         case 1:
              printf("Seta desesporada\n");
              break;
     }
}
void plantsInPool(int level){
     switch(level){
         case 1:
              printf("Nenufar\n");
              break;
     }
}
void plantsInFog(int level){
     switch(level){
         case 1:
              printf("Marceta\n");
              break;
     }
}
void plantsInRoof(int level){
     switch(level){
         case 1:
              printf("Coltapulta\n");
              break;
     }
}

void desbloquearPlanta(int stage, int level){
   enum Plant newPlant;
   if(stage == 1){
     switch(level){
         case 1:
               newPlant = lanzaguisantes;
               insertPlantInDeck(newPlant);
               printf("lanzaguisantes insertado en la baraja\n");
               break;
         case 2:
               newPlant = girasol;
               insertPlantInDeck(newPlant);
               printf("insertar girasol\n");
               break;
         case 3:
               newPlant = petacereza;
               insertPlantInDeck(newPlant);
               printf("insertar Petacereza\n");
               break;
         case 4:
               newPlant = nuez;
               insertPlantInDeck(newPlant);
               printf("insertar nuez\n");
               break;
         case 5:
               newPlant = patapum;
               insertPlantInDeck(newPlant);
               printf("insertar Patapum\n");
               break;
         case 6:
               newPlant = hielaguisantes;
               insertPlantInDeck(newPlant);
               printf("insertar Hielaguizantes\n");
               break;
         default:
               // En este nivel ya debe permitir mostrar el menu
               printf("Mostrar menu");
               break;
     }
   }
}       

void plantsInShop(int item){
}

void generadorDeLanzaguisantes(Lanzaguisantes *plant){
     //plant->body.rec.width = 26;
     //plant->body.rec.height = 32;
     plant->body.gameObject.size.x = 26;
     plant->body.gameObject.size.y = 32;
     plant->body.life = 300;
     plant->body.damage = grande;
     plant->body.cost = 100;
     plant->body.chargeTimeMax = rapida*60;
     plant->body.bulletTimeMax = bullet_rapida*60;
     plant->body.timer = 0;
     plant->body.timerBullet = 0;
     //loadLanzaguisantesAnim(&plant->body);
}

void generarProyectil(Plants plant, Projectile *newBullet){
     //newBullet->rec.x = plant.rec.x+10;
     //newBullet->rec.y = plant.rec.y;
     newBullet->rec.x = plant.gameObject.size.x+10;
newBullet->rec.y = plant.gameObject.size.y;
     newBullet->rec.width = 16;
     newBullet->rec.height = 16;
     newBullet->damage = plant.damage;
     newBullet->exist = true;
     //loadProjectileAnim(newBullet);
     //printf("disparar\n");
}