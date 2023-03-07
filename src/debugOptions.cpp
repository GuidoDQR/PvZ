#include "debugOptions.hpp"

Tyra::Sprite debug_sprite;
//DebugBox* debug_box_col;

int  optiondebug1 = null;
int  debug_render_size_map_x = 0;
int  debug_render_size_map_y = 0;
bool optiondebug2           = false;
bool b_debug                = false;
bool b_debugSprite          = false;
bool b_debugHidebackground  = false;
bool b_debugBox             = false;
bool b_debugMap             = false;
bool b_debugAnimation       = false;

DebugBox::DebugBox(){
  gameObject.anim.NewSprite();
  gameObject.anim.stopRender = true;
  Tyra::Sprite* newSprite = gameObject.anim.GetSprite(0);
  *newSprite = box.sprite;
  collider = newSprite;
  //printf("pase por debug box\n\n");
  //printf("\n\n\n\n\n");
}

void ShowDebugOptions(){
    printf("\n");
    for(int i=d_firstOption; i< d_maxOptions;i++){
        if(optiondebug1 == i){printf("--> ");}
        else{printf("    ");}

        switch (i){
            case d_sprite:
              TYRA_LOG ("SPRITE DEBUG MODE");
              break;
            case d_box:
              TYRA_LOG ("BOX DEBUG MODE");        
              break;
            case d_hidebackground:
              TYRA_LOG ("HIDE BACKGROUND"); 
              break;         
            case d_map:
              TYRA_LOG ("SHOW MAP  MODE");   
              break;
            case d_cursorPlayer1:
              TYRA_LOG ("CURSOR PLAYER 1 MODE");
              break;
            case d_animation:
              TYRA_LOG ("ANIMATION MODE");
              break;
            default:
              break;
        }
    }
}

void DebugCrossOptions(){
  switch (optiondebug1){
  case d_sprite:
    b_debugSprite = true;  
    TYRA_WARN("\nSPRITE DEBUG MODE ACTIVATE\n"); 
    break;
  case d_box:
    b_debugBox = true;
    TYRA_WARN("\nBOX DEBUG MODE ACTIVATE\n");
    break;
  case d_hidebackground:
    b_debugHidebackground = !b_debugHidebackground;
    if(b_debugHidebackground) TYRA_WARN("\nHIDE BACKGROUND ACTIVATE\n");     
    else{ TYRA_WARN("\nHIDE BACKGROUND DEACTIVATE\n"); ShowDebugOptions();} 
    break;
  case d_map:
    b_debugMap = !b_debugMap;

    if(b_debugMap){TYRA_WARN("\nMAP DEBUG MODE ACTIVATE\n");}
    else{ TYRA_WARN("\nMAP DEBUG MODE DEACTIVATE\n"); ShowDebugOptions();}
    break;
  case d_cursorPlayer1:
  break;
  case d_animation:
    if(!b_debugAnimation){
      b_debugAnimation = true;
      TYRA_WARN("\nANIMATION MODE ACTIVATE\n");
    }   
  break;
  
  default:
    break;
  }
}

void DebugCircleOptions(){

  switch (optiondebug1){
  case d_sprite:
    b_debugSprite = false;
    TYRA_WARN("\nSPRITE DEBUG MODE DEACTIVATE\n");
    break;
  case d_hidebackground:
    b_debugHidebackground = false;
    TYRA_WARN("\nHIDE BACKGROUND DEACTIVATE\n"); 
    break;
  case d_box:
    b_debugBox = false;
    TYRA_WARN("\nBOX DEBUG MODE DEACTIVATE\n");
    break;
  case d_map:
    b_debugMap = !b_debugMap;
    if(b_debugMap)TYRA_WARN("\nMAP DEBUG MODE ACTIVATE\n");
            else  TYRA_WARN("\nMAP DEBUG MODE DEACTIVATE\n");
    break;
  case d_animation:
    if(b_debugAnimation){
      b_debugAnimation = false;
      TYRA_WARN("\nANIMATION MODE DEACTIVATE\n");
    }
    break;
  default:
    break;
  }
        
}