#include "deck.hpp"
#include <stdio.h>
unsigned int max_deck = 6;

enum Plant deck[8];

unsigned int counterPlants = 0;       // Cuenta la cantidad de plantas que estan en el deck   

void set_Max_Deck(unsigned int newMax){ max_deck = newMax; }

// Plantas que estaran en el mazo
void plantsInDeck(){

}

void insertPlantInDeck(enum Plant newPlantInDeck){
     deck[counterPlants] = newPlantInDeck;
     printf("inserted in deck[%d] = %d\n",counterPlants, newPlantInDeck);
     counterPlants++;
}

// Plantas desbloqueadas en el juego
void plantsUnlocked(unsigned int countLevel){

}      