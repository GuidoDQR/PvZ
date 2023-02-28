#include "game_state.hpp"
#include "textures.hpp"
#include "plants.hpp"
#include "zombies.hpp"
#include "Fonts.hpp"
//#include <time.h>   

using namespace Tyra;

Game_state::Game_state(Engine* t_engine, Pad* t_pad1, const char* new_imageFile, state newState) : camera1(t_engine){
    engine = t_engine;
    pad1 = t_pad1;
    imageFile = new_imageFile;
    colorState = newState;
    initialized = false;
}

Game_state::~Game_state(){
    //engine->renderer.getTextureRepository().freeBySprite(background);
}

void Game_state::init(){
    timer.prime();

    LoadSprite(background.anim.NewSprite(), Vec2{-56,-1},Vec2{780,524});
    //printf("init backSprite id: %d\n",background.sprite->id);
    LoadTexture(background.sprite, imageFile, engine);

    //background.sprite->size.x = 100;
    //background.sprite->size.y = 100;
    //printf("id: %d\n",background.anim.GetSprite(0)->id);
    //printf("pos: %f,%f\n",background.anim.GetSprite(0)->position.x,background.anim.GetSprite(0)->position.y);
    //printf("size: %f,%f\n",background.anim.GetSprite(0)->size.x,background.anim.GetSprite(0)->size.y);
   
    //printf("textures count: %u\n", engine->renderer.getTextureRepository().getTexturesCount());

    cameraPosition = Vec4(0.0F, 0.0F, -10.0F);
    cameraLookAt.unit();

    soles = 225;

    // Plantas

    //Lanzaguisantes plant_lanzaguisantes;
    //generadorDeLanzaguisantes(&plant_lanzaguisantes);

    const int maxBullets = 550;
    Projectile bullets[maxBullets];
    int bulletCounter = 0;

    // Zombies

    const int maxZombies = 3;
    Zombies *zombie = new Zombies[maxZombies];
    int zombieCounter = 0;
    int zombieGenerate = 0;

    const int maxSol = 50;
    Sol sol[maxSol];
    int solCounter = 0;

    srand(time(NULL));          

    bool gameComplete = false;
    int  stage = 1;
    int  level = 1;     

    plantsInLevel(stage,level);   
      
    // En los primeros niveles se insertan, SOLAMENTE SI NO COMPLETO EL NIVEL
    // En la baraja las primeras cartas se insertan de forma automatica

    desbloquearPlanta(stage, level);

    if (gameComplete == false){
        unsigned int counterLevel = stage * level;
        plantsUnlocked(counterLevel); // Desbloquea las plantas en base a la suma de los niveles en el que esta
    }    

    // Map
    size_map_x = 5;//5
    size_map_y = 9;//9

    Rectangle linesMap[size_map_y];             // Verifica si colisiona con un zombie
    bool mapHasZombies[size_map_x][size_map_y]; // Verifica si hay un zombie en el mapa
    bool mapHasPlant[size_map_x][size_map_y];   // Verifica si hay una planta en el mapa
    //Plants mapPlants[size_map_x][size_map_y];   // lugar donde esta la planta

    float posY = 58;
    for(int i=0; i<size_map_x;i++){
      float posX = 85;
      for(int j=0; j<size_map_y;j++){
        //map[i][j].sprite.color = Color(0,255,0,128);
        //map[i][j].sprite.position = Vec2(posX,posY); // 85,58
        //map[i][j].sprite.size = Vec2(45,72);
        //map[i][j].gameObject.anim.SetPositionFrameBySpriteSize(0,Vec2(posX,posY));
        //map[i][j].gameObject.anim.GetSprite(0)->size = Vec2(45,72);
        map[i][j].collider->position = Vec2(posX,posY);
        map[i][j].collider->size = Vec2(45,72);
        mapHasPlant[i][j] = false;
        posX += 45;
      }
      posY += 72;
    }

    //int actualMapX = 0; // sector del mapa donde esta el cursor
    //int actualMapY = 0; // sector del mapa donde esta el cursor
    //int centerMapX = map[0][0].sprite.position.x + (map[0][0].sprite.size.x/2);     // Centro del sector donde esta el cursor
    //int centerMapY = map[0][0].sprite.position.y + (map[0][0].sprite.size.y/2);     // Centro del sector donde esta el cursor

    int centerMapX = map[0][0].gameObject.anim.GetPositionFrame(0).x + (map[0][0].gameObject.anim.GetSprite(0)->size.x/2);     // Centro del sector donde esta el cursor
    int centerMapY = map[0][0].gameObject.anim.GetPositionFrame(0).y + (map[0][0].gameObject.anim.GetSprite(0)->size.y/2);     // Centro del sector donde esta el cursor
    // Players Controls

    //cursorPlayer.sprite.size.x = 48; // width //48
    //cursorPlayer.sprite.size.y = 56; // height  //56
    cursorPlayer.gameObject.size.x = 48;
    cursorPlayer.gameObject.size.y = 56;
    cursorPlayer.gameObject.position.x = centerMapX - (cursorPlayer.gameObject.size.x/2);
    cursorPlayer.gameObject.position.y = centerMapY - (cursorPlayer.gameObject.size.y/2) - 30;
    //cursorPlayer.sprite.position.x = centerMapX - (cursorPlayer.sprite.size.x/2);
    //cursorPlayer.sprite.position.y = centerMapY - (cursorPlayer.sprite.size.y/2) - 30;
    //cursorPlayer.center = cursorPlayer.sprite.position;
    cursorPlayer.center = cursorPlayer.gameObject.position;

    cursorPlayer.deckPosX = 0; // sector del mapa donde esta el cursor
    cursorPlayer.deckPosY = 0; // sector del mapa donde esta el cursor

    cursorPlayer.offset.x = 12;
    cursorPlayer.offset.y = 14; //20 para moverlo mas arriba
    cursorPlayer.collider[0].sprite.position = Vec2(cursorPlayer.gameObject.position.x + cursorPlayer.offset.x,cursorPlayer.gameObject.position.y + cursorPlayer.offset.y);
    cursorPlayer.collider[0].sprite.size = Vec2(24,28);

    //LoadSprite(&cursorPlayer.sprite,
    //          Vec2(cursorPlayer.sprite.position.x,cursorPlayer.sprite.position.y),
    //          Vec2(cursorPlayer.sprite.size.x,cursorPlayer.sprite.size.y));
    
    LoadSprite(cursorPlayer.gameObject.anim.NewSprite(),Vec2(0,0),Vec2(cursorPlayer.gameObject.size.x,cursorPlayer.gameObject.size.y));
    //cursorPlayer.gameObject.anim.SetPositionFrameBySpriteSize(cursorPlayer.gameObject.anim.SpriteSize()-1,cursorPlayer.gameObject.a);
    LoadTexture(cursorPlayer.gameObject.anim.GetSprite(cursorPlayer.gameObject.anim.SpriteSize()-1),"cursor6.png", engine);
    //LoadTexture(&cursorPlayer.sprite,"cursor6.png", engine);

    cursorPlayer.isMove = false;
    cursorPlayer.isCenter = true;

    //Plants cursorPlant;
    //cursorPlant = plant_lanzaguisantes.body;

    //cursorSelect.sprite.position.x = 132;
    //cursorSelect.sprite.position.y = 0;

    cursorSelect.gameObject.position.x = 132;
    cursorSelect.gameObject.position.y = 0;

    // Timers

    tim_cursorPlant = 0;   // Selecciona en donde se implementa la planta
    tim_cursorSelect = 0;  // Selecciona la planta que se puede plantar
    tim_sol = 0;           // Cantidad de tiempo para generar el sol
    tim_zombie = 0;        // Cantidad de tiempo para generar el zombie

    Sol solSpriteText;
    solSpriteText.rec.x = 108;
    solSpriteText.rec.y = 5;
    solSpriteText.rec.width = 26;
    solSpriteText.rec.height = 26;

    //char *solesText; // Texto de la cantidad de soles
    //sprintf(solesText, "%d", soles); // convierte el int a string    

    solesText = std::to_string(soles);
    initialized = true;

    //debug
    box = Vec4(0.0F, 0.0F, 0.0F);
    debug_render_size_map_x = size_map_x;
    debug_render_size_map_y = size_map_y;
    //size = 0.2f;
    // Debug sprites
    LoadSprite(&debug_sprite, Vec2{0,0},Vec2{256,128});

    //box_col.gameObject.position = Vec2(85,58);
    //box_col.gameObject.size = Vec2(45,72);
    //loadTexture(engine,&debug_sprite,"Animations/PeaShooterSingle/0001.png");
    //LoadTexture(&debug_sprite,"cursor6.png",engine);
    
    box_col.gameObject.position = Vec2(0,0);
    box_col.collider->size.x = 45;
    box_col.collider->size.y = 72;

}

void Game_state::loop(){
    //TYRA_LOG("LOOP STATE!"); 
    //printf("timer: %d\n",timer.getTimeDelta());

    if(pad1->getClicked().R1){
      b_debug = !b_debug;
      if(b_debug){
        optiondebug1 = d_sprite;
        TYRA_WARN("DEBUG MODE ACTIVATE");
        ShowDebugOptions(); 
      } else {TYRA_WARN("DEBUG MODE DEACTIVATE"); optiondebug1 = null;/* debugOption = null;*/} 
    }                 

    if(b_debug){     

      // las cajas de box collider deben estar en la posicion: 85,58. tamaño:45,72

      if(timer.getTimeDelta()> 2000){

        if(/*pad1->getLeftJoyPad().v <= 100 ||*/ pad1->getPressed().DpadUp && !b_debugSprite && !b_debugBox){
          optiondebug1--;
          if(optiondebug1 < d_firstOption){ optiondebug1 = d_maxOptions-1;}
          
          ShowDebugOptions();

          timer.prime();
        }else if(/*pad1->getLeftJoyPad().v >= 200 ||*/ pad1->getPressed().DpadDown && !b_debugSprite && !b_debugBox){
          optiondebug1++;
          if(optiondebug1 > d_maxOptions-1){ optiondebug1 = d_firstOption;}

          ShowDebugOptions();
          
          timer.prime();
        }
      } 

        // Cross options
        if(pad1->getClicked().Cross){

          switch (optiondebug1){
          case d_sprite:
            if(!b_debugSprite){
              b_debugSprite = true;  
              TYRA_WARN("\nSPRITE DEBUG MODE ACTIVATE\n"); 
            }
            break;
          case d_hidebackground:
            background.anim.stopRender = !background.anim.stopRender;

            if(background.anim.stopRender) TYRA_WARN("\nHIDE BACKGROUND ACTIVATE\n");     
            else{ TYRA_WARN("\nHIDE BACKGROUND DEACTIVATE\n"); ShowDebugOptions();}   
            break;
          case d_box:
            if(!b_debugBox){
              b_debugBox = true;
              box_col.gameObject.anim.stopRender = false;
              printf("GO stopRender: %d\n",box_col.gameObject.anim.stopRender);
              TYRA_WARN("\nBOX DEBUG MODE ACTIVATE\n");
            }
            break;
          case d_map:
            b_debugMap = !b_debugMap;

            for(int i=0;i<debug_render_size_map_x;i++){
              for(int j=0;j<debug_render_size_map_y;j++){
                map[i][j].gameObject.anim.stopRender = !b_debugMap;
              }
            }

            if(b_debugMap){TYRA_WARN("\nMAP DEBUG MODE ACTIVATE\n");}
            else{ TYRA_WARN("\nMAP DEBUG MODE DEACTIVATE\n"); ShowDebugOptions();}
            break;
          default:
            break;
          }
          
        }
        
        // Circle options
        if(pad1->getClicked().Circle){
          if(optiondebug1 == d_sprite && b_debugSprite){    
            b_debugSprite = false;
            TYRA_WARN("\nSPRITE DEBUG MODE DEACTIVATE\n");
          }else if(optiondebug1 == d_hidebackground ){
            background.anim.stopRender = false;

            TYRA_WARN("\nHIDE BACKGROUND DEACTIVATE\n"); 
          }else if(optiondebug1 == d_box && b_debugBox){
            b_debugBox = false;
            box_col.gameObject.anim.stopRender = true;
            printf("GO stopRender: %d\n",box_col.gameObject.anim.stopRender);
            TYRA_WARN("\nBOX DEBUG MODE DEACTIVATE\n");
          }else if(optiondebug1 == d_map ){
            b_debugMap = !b_debugMap;

            for(int i=0;i<debug_render_size_map_x;i++){
              for(int j=0;j<debug_render_size_map_y;j++){
                map[i][j].gameObject.anim.stopRender = !b_debugMap;
              }
            }

            if(b_debugMap)TYRA_WARN("\nMAP DEBUG MODE ACTIVATE\n");
            else TYRA_WARN("\nMAP DEBUG MODE DEACTIVATE\n");
          }

          ShowDebugOptions(); 
        }

        
        
        

        if(b_debugSprite == true){
      
          // se usa para cambiar el tamaño y posicion del sprite para probar

          if(pad1->getLeftJoyPad().v <= 100 ){
            speedCountY++;
            speedY = -1;       
            if(speedCountY > 5){speedY = -2;}
            else if(speedCountY > 10){speedY = -3;}
            timer.prime();
          }else if(pad1->getLeftJoyPad().v >= 200 ){
            speedCountY++;
            speedY = 1;          
            if(speedCountY > 5){ speedY = 2;}
            else if(speedCountY > 10){speedY = 3;}
            timer.prime();
          }else{ speedCountY = 0; speedY = 0;}

          if(pad1->getLeftJoyPad().h <= 100 ){
            speedX = -1;
            speedCountX++;
            if(speedCountX > 5){speedX = -2;}
            else if(speedCountX > 10){speedX = -3;} 
            timer.prime();
          }else if(pad1->getLeftJoyPad().h >= 200 ){
            speedX = 1;
            speedCountX++;
            if(speedCountX > 5){speedX = 2;}
            else if(speedCountX > 10){speedX = 3;}           
            timer.prime();
          }else{ speedCountX = 0; speedX = 0;}

          if(speedX !=0 || speedY != 0){
            debug_sprite.position += Vec2(speedX, speedY);
            printf("position: (%f,%f)\n",debug_sprite.position.x,debug_sprite.position.y);
          }

          if(pad1->getRightJoyPad().v <= 100){
            debug_sprite.size.y -= 1.0f;
            printf("size: (%f,%f)\n",debug_sprite.size.x,debug_sprite.size.y);
            timer.prime();
          }else if(pad1->getRightJoyPad().v >= 200 ){
            debug_sprite.size.y += 1.0f;
            printf("size: (%f,%f)\n",debug_sprite.size.x,debug_sprite.size.y);
            timer.prime();
          }

          if(pad1->getRightJoyPad().h >= 200 ){
            debug_sprite.size.x += 1.0f;
            printf("size: (%f,%f)\n",debug_sprite.size.x,debug_sprite.size.y);
            timer.prime();
          }else if(pad1->getRightJoyPad().h <= 100 ){
            debug_sprite.size.x -= 1.0f;
            printf("size: (%f,%f)\n",debug_sprite.size.x,debug_sprite.size.y);
            timer.prime();
          }
                 
          if(pad1->getPressed().Triangle){
            debug_sprite.size += Vec2(1.0F, 1.0F);
            printf("size: (%f,%f)\n",debug_sprite.size.x,debug_sprite.size.y);
            timer.prime();
          }else if(pad1->getPressed().Square){
            debug_sprite.size -= Vec2(1.0F, 1.0F);
            printf("size: (%f,%f)\n",debug_sprite.size.x,debug_sprite.size.y);
            timer.prime();
          }
        }

        if(b_debugBox == true){
          // se usa para cambiar el tamaño y posicion del box para probar

          if(pad1->getLeftJoyPad().v <= 100 ){
            box_col.gameObject.position.y -= 1.0F;
            printf("position: (%f,%f)\n",box_col.gameObject.position.x,box_col.gameObject.position.y);
            timer.prime();
          }else if(pad1->getLeftJoyPad().v >= 200 ){
            box_col.gameObject.position.y += 1.0F;
            printf("position: (%f,%f)\n",box_col.gameObject.position.x,box_col.gameObject.position.y);
            timer.prime();
          }

          if(pad1->getLeftJoyPad().h <= 100 ){
            box_col.gameObject.position.x -= 1.0F;
            printf("position: (%f,%f)\n",box_col.gameObject.position.x,box_col.gameObject.position.y);
            timer.prime();
          }else if(pad1->getLeftJoyPad().h >= 200 ){
            box_col.gameObject.position.x += 1.0F;
            printf("position: (%f,%f)\n",box_col.gameObject.position.x,box_col.gameObject.position.y);
            timer.prime();
          }
          
          if(pad1->getRightJoyPad().v <= 100){
            box_col.collider->size.y -= 1.0f;
            printf("size: (%f,%f)\n",box_col.collider->size.x,box_col.collider->size.y);
            timer.prime();
          }else if(pad1->getRightJoyPad().v >= 200 ){
            box_col.collider->size.y += 1.0f;
            printf("size: (%f,%f)\n",box_col.collider->size.x,box_col.collider->size.y);
            timer.prime();
          }

          if(pad1->getRightJoyPad().h >= 200 ){
            box_col.collider->size.x += 1.0f;
            printf("size: (%f,%f)\n",box_col.collider->size.x,box_col.collider->size.y);
            timer.prime();
          }else if(pad1->getRightJoyPad().h <= 100 ){
            box_col.collider->size.x -= 1.0f;
            printf("size: (%f,%f)\n",box_col.collider->size.x,box_col.collider->size.y);
            timer.prime();
          }

          if(pad1->getPressed().Triangle){
            box_col.collider->size += Vec2(1.0F, 1.0F);
            printf("size: (%f,%f)\n",box_col.collider->size.x, box_col.collider->size.y);
            timer.prime();
          }else if(pad1->getPressed().Square){
            box_col.collider->size -= Vec2(1.0F, 1.0F);
            printf("size: (%f,%f)\n",box_col.collider->size.x, box_col.collider->size.y);
            timer.prime();
          }
        }
      }

      
      


    //if(timer.getTimeDelta()> 1000){ // sin esto es dependiente del framerate, pero ahora anda mas fluido 
        // cursor movement

        if(pad1->getLeftJoyPad().v <= 100 ){
          speedCountY++;
          speedY = -2;       
          if(speedCountY > 10){speedY = -4;}
          else if(speedCountY > 3){speedY = -3;}
          timer.prime();
        }else if(pad1->getLeftJoyPad().v >= 200 ){
          speedCountY++;
          speedY = 2;          
          if(speedCountY > 10){ speedY = 4;}
          else if(speedCountY > 3){speedY = 3;}
          timer.prime();
        }else{ speedCountY = 0; speedY = 0;}
        

        if(pad1->getLeftJoyPad().h <= 100 ){
          speedX = -2;
          speedCountX++;
          if(speedCountX > 10){speedX = -4;}
          else if(speedCountX > 3){speedX = -3;} 
          timer.prime();
        }else if(pad1->getLeftJoyPad().h >= 200 ){
          speedX = 2;
          speedCountX++;
          if(speedCountX > 10){speedX = 4;}
          else if(speedCountX > 3){speedX = 3;}           
          timer.prime();
        }else{ speedCountX = 0; speedX = 0;}
        
        if(speedX !=0 || speedY != 0){           
          cursorPlayer.isMove = true;
          cursorPlayer.isCenter = false;
          //cursorPlayer.sprite.position += Vec2(speedX, speedY);
          cursorPlayer.gameObject.position += Vec2(speedX, speedY);
          cursorPlayer.collider[0].sprite.position += Vec2(speedX, speedY);

          // Limits of the map

          Vec2 colPos = cursorPlayer.collider[0].sprite.position;
          Vec2 colSize = cursorPlayer.collider[0].sprite.size;
          Vec2 colMapInitial = map[0][0].gameObject.anim.GetSprite(0)->position;
          Vec2 colMapRight   = map[0][size_map_y-1].gameObject.anim.GetSprite(0)->position;
          Vec2 colMapRightSize = map[0][size_map_y-1].gameObject.anim.GetSprite(0)->size;
          Vec2 colMapLeft    = map[size_map_x-1][0].gameObject.anim.GetSprite(0)->position;
          Vec2 colMapLeftSize  = map[size_map_x-1][0].gameObject.anim.GetSprite(0)->size;

          if(colPos.x < (colMapInitial.x - colSize.x/2)){
            cursorPlayer.collider[0].sprite.position.x = colMapInitial.x  - colSize.x/2;

            //cursorPlayer.sprite.position = cursorPlayer.collider[0].sprite.position - colSize/2;
            cursorPlayer.gameObject.position = cursorPlayer.collider[0].sprite.position - colSize/2;
          }else if(colPos.x> colMapRight.x + colMapRightSize.x - (colSize.x/2)){
            cursorPlayer.collider[0].sprite.position.x = colMapRight.x + colMapRightSize.x - (colSize.x/2);

            //cursorPlayer.sprite.position = colPos - colSize/2;
            cursorPlayer.gameObject.position = colPos - colSize/2;
             
            //printf("cursor collider pos: (%f,%f)\n",cursorPlayer.collider.sprite.position.x,cursorPlayer.collider.sprite.position.y);
            //printf("map[%d][%d] pos: %f,%f\n",0,size_map_y-1,colMapRight.x, colMapRight.y );
            //printf("map[%d][%d] size: %f,%f\n",0,size_map_y-1,colMapRightSize.x, colMapRightSize.y );
            //printf("cursor size: (%f,%f)\n",cursorPlayer.sprite.size.x,cursorPlayer.sprite.size.y);
          }

          if(colPos.y < (colMapInitial.y - colSize.y/2)){
            cursorPlayer.collider[0].sprite.position.y = colMapInitial.y  - colSize.y/2;

            //cursorPlayer.sprite.position = colPos - colSize/2;
            cursorPlayer.gameObject.position = colPos - colSize/2;
          }else if(colPos.y > colMapLeft.y + colMapLeftSize.y - (colSize.y/2)){
            cursorPlayer.collider[0].sprite.position.y = colMapLeft.y +colSize.y - (colSize.y/2);

            //cursorPlayer.sprite.position = colPos - colSize/2;
            cursorPlayer.gameObject.position = colPos - colSize/2;
          }
          
        }else{ cursorPlayer.isMove = false;}

        // CursorPlayer collision with map
        if(cursorPlayer.isMove){
          for(int i=0; i<size_map_x;i++){
            for(int j=0;j<size_map_y;j++){
              if(ColliderCollision(cursorPlayer.collider[0].sprite, *map[i][j].gameObject.anim.GetSprite(0))){
                //printf("\nCursor in map[%d][%d]\n",i,j);
                cursorPlayer.deckPosX = i;
                cursorPlayer.deckPosY = j;
                i = size_map_x;
                j = size_map_y;
              }
            }
          }         
        }

        if(!cursorPlayer.isCenter && !cursorPlayer.isMove){
          Vec2 centerMap = map[cursorPlayer.deckPosX][cursorPlayer.deckPosY].gameObject.anim.GetSprite(0)->position + (map[cursorPlayer.deckPosX][cursorPlayer.deckPosY].gameObject.anim.GetSprite(0)->size/2) - (cursorPlayer.gameObject.size.x/2);
          centerMap.y -= 30; // offsetY

          /*printf("center map: (%f,%f)\n",centerMap.x,centerMap.y);
          printf("map[%d][%d], pos: %f,%f\n",cursorPlayer.posX,cursorPlayer.posY,map[cursorPlayer.posX][cursorPlayer.posY].sprite.position.x, map[cursorPlayer.posX][cursorPlayer.posY].sprite.position.y );
          printf("map[%d][%d], size: %f,%f\n",cursorPlayer.posX,cursorPlayer.posX,map[cursorPlayer.posX][cursorPlayer.posY].sprite.size.x, map[cursorPlayer.posX][cursorPlayer.posY].sprite.size.y );
          printf("cursor position: (%f,%f)\n\n",cursorPlayer.sprite.position.x,cursorPlayer.sprite.position.y);*/
          Vec2* playerPos = &cursorPlayer.gameObject.position;
          if((playerPos->x - centerMap.x > 0 && playerPos->x - centerMap.x <= 2) || 
             (playerPos->x - centerMap.x < 0 && playerPos->x - centerMap.x >= -2)){
              playerPos->x = centerMap.x;
              cursorPlayer.collider[0].sprite.position.x = centerMap.x  + cursorPlayer.collider[0].sprite.size.x/2 ;
              //printf("\ncentre en X\n");
          }else if(playerPos->x> centerMap.x){
            playerPos->x -= 2;
            cursorPlayer.collider[0].sprite.position.x -= 2;
          }else if(playerPos->x < centerMap.x){
            playerPos->x += 2;
            cursorPlayer.collider[0].sprite.position.x += 2;
          }else 

          if((playerPos->y - centerMap.y > 0 && playerPos->y - centerMap.y <= 2) || 
             (playerPos->y - centerMap.y < 0 && playerPos->y - centerMap.y >= -2)){
              playerPos->y = centerMap.y;
              cursorPlayer.collider[0].sprite.position.y = centerMap.y /*+ cursorPlayer.offset.y/2*/ + cursorPlayer.collider[0].sprite.size.y/2;;
              //printf("\ncentre en Y\n");
          }else if(playerPos->y > centerMap.y){
            playerPos->y -= 2;
            cursorPlayer.collider[0].sprite.position.y -= 2;
          }else if(playerPos->y < centerMap.y){
            playerPos->y += 2;
            cursorPlayer.collider[0].sprite.position.y += 2;
          }

          if((playerPos->x ) == centerMap.x && (playerPos->y)== centerMap.y){
            cursorPlayer.isCenter = true;
            /*printf("esta en el centro\n");
            printf("cursor position: (%f,%f)\n",cursorPlayer.sprite.position.x,cursorPlayer.sprite.position.y);*/
          }

        }
    //}

    auto& renderer = engine->renderer;

    //auto& utilityTools = renderer.renderer3D.utility;

    /** Begin frame will clear our screen. */
    renderer.beginFrame();
    
    //renderer.beginFrame(CameraInfo3D(&cameraPosition, &cameraLookAt));
    
    GOmanager.Render();
    
    // debug ifs

    std::string texto = "hola mundo"; 
    DrawText(solesText,50,50);
    //utilityTools.drawLine(Vec4(50.0F, 50.0F, 50.0F),Vec4(0.0F, 0.0F, 0.0F),Color(0.0F, 128.0F, 0.0F));
    //utilityTools.drawBox(box, size, Color(0.0F, 0.0F, 255.0F));
    /** End frame will perform vsync. */
    renderer.endFrame();
}
