#pragma once

#include "debugOptions.hpp"
#include "global_state_type.hpp"
#include "miscellaneous.hpp"
#include "controls.hpp"
#include "Camera.hpp"
#include "gameObject.hpp"
#include <tyra>

class Game_state : public Tyra::Game {
 public:
  Game_state(Tyra::Engine* engine, Tyra::Pad* pad1, const char* imageFile, state newState);
  ~Game_state();

  void init();
  void loop();

  state colorState;
  bool initialized;
 private:
  Tyra::Vec4 cameraPosition;
  Tyra::Vec4 cameraLookAt;

  Tyra::Engine* engine;    
  Tyra::Pad* pad1;

  Camera camera1;

  //Tyra::Sprite background;
  GameObject background;
  
  Tyra::Timer timer;
  Tyra::AudioSong song;
  const char* imageFile;
  int soles;  

  Cursor cursorPlayer;
  Cursor cursorSelect;

  int tim_cursorPlant;   // Selecciona en donde se implementa la planta
  int tim_cursorSelect;  // Selecciona la planta que se puede plantar
  int tim_sol;           // Cantidad de tiempo para generar el sol
  int tim_zombie;        // Cantidad de tiempo para generar el zombie

  int size_map_x;
  int size_map_y;
  
  Map map[10][10];

  std::string solesText; // Texto de la cantidad de soles

  int speedCountX = 0;
  int speedCountY = 0;
  float speedX = 1;
  float speedY = 1;
  // Debug variables
  //int debugOption = 0;
  
  DebugBox box_col;
  Tyra::Vec4 box;  
  Tyra::Vec2 size;
};
