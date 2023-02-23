#pragma once

#include "game_state.hpp"
//#include "debug/debugGame.hpp"
//#include <tyra>

//namespace GameMain {

class Game_Manager : public Tyra::Game{
 public:
  Game_Manager(Tyra::Engine* engine);
  ~Game_Manager();

  void init();
  void loop();

 private:
  Tyra::Engine* engine;
  Tyra::Pad* pad1;
  //DebugGame::DebugMenu debug;
  
  std::vector<Game_state*> stateManager;
  state currentState;

};

//}  // namespace GameMain
