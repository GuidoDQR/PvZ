#include "gameManager.hpp"

//namespace GameMain {

using namespace Tyra;

Game_Manager::Game_Manager(Engine* t_engine) : engine(t_engine){}
Game_Manager::~Game_Manager() {}

void Game_Manager::init() { 
    TYRA_LOG("Hello!"); 
    pad1 = &engine->pad;
    currentState = mainGame;

    
    //debug.setPad(pad1);   
   
    stateManager.push_back(new Game_state(engine, pad1, "Backgrounds/Day.png", mainGame));
    //stateManager.push_back(new Game_state(engine, pad1, "Animations/PeaShooterSingle/0002.png", mainMenu));
    //stateManager.push_back(new Game_state(engine, pad1, "Animations/PeaShooterSingle/0003.png", intro));
}

void Game_Manager::loop() { 
    /*if(pad1->getClicked().Cross){
        currentState = mainGame;
    }else if(pad1->getClicked().Square){
        currentState = mainMenu;
    }else if(pad1->getClicked().Triangle){
        currentState = intro;
    }*/


    for (auto& state : stateManager) {
        //TYRA_LOG("PASE!"); 
      if (state->colorState == currentState) {
        if(state->initialized == false){
            state->init();
        }

        state->loop();
        break;
      }
    }

   // stateMain.loop();
    
}

//}  // namespace Racer
