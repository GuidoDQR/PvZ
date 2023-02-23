#include "animation.hpp"
#include "Camera.hpp"
#include <string>

using namespace Tyra;

//std::vector<int> totalLayers;

/*void OrderLayers(){
  for(int i=totalLayers.size();i>0;i--){
    if(totalLayers[i] < totalLayers[i-1]){
      int aux = totalLayers[i];
      totalLayers[i] = totalLayers[i-1];
      totalLayers[i-1] = aux;
    }else{ break; }  
  }
}*/

Animation::Animation(){
  Camera camera;
  engine          = camera.renderCamera();
  frame           = 0;
  firstFrame      = finalFrame = 0;
  firstImageFrame = finalImageFrame = 0;
  timer           = 0;
  seconds         = 0.6f;
  reverseFrame = stopFrame = stopRender = false;
  position     = new Vec2(0,0);
  sprite = std::vector<Sprite*>(0);

  //if(totalLayers.size() == 0){ totalLayers.push_back(0);}
  //printf("creado\n");
  sprite.clear();
}

Animation::Animation(Engine* t_engine, Vec2* gameObjectPosition) { 
  engine          = t_engine;
  frame           = 0;
  firstFrame      = finalFrame = 0;
  firstImageFrame = finalImageFrame = 0;
  timer           = 0;
  seconds         = 0.6f;
  reverseFrame = stopFrame = stopRender = false;
  position     = gameObjectPosition;
  //sprite.resize(0);
  //sprite.assign(0,0);
  //printf("size layer 1: %d\n",totalLayers.size());
  //if(totalLayers.size() == 0){ totalLayers.push_back(0); /*printf("size layer 2: %d\n",totalLayers.size());*/}
  sprite.resize(0);
  //printf("creado\n");
  //sprite.clear();
}

Animation::~Animation() { 
  for(unsigned int i = firstFrame; i < finalFrame; i++){
    engine->renderer.getTextureRepository().freeBySprite(*sprite[i]);
    engine->renderer.getTextureRepository().freeBySprite(spriteFrame[i]);
  }   
}

void Animation::SetRender(Engine* t_engine){ engine = t_engine; }

void Animation::SetPositionGameObject(Vec2* newPos){
  position = newPos; printf("Position Animation: (%f,%f)\n", position->x , position->y);
}

void Animation::SetImagePNG(const char* newImage, const int initialFrame, const int lastFrame){
  TYRA_LOG("Setting Image"); 
  image = newImage;
  frame = initialFrame;
  firstFrame = initialFrame;
  finalFrame = lastFrame;
  std::string fileString;  
  for(int i=initialFrame; i< lastFrame; i++){    
        fileString = image; 
        if(i<9){
          for(int j=0;j<3;j++){ fileString += std::to_string(0); }
          fileString += std::to_string(i+1);
        }else if(i < 99){
          for(int j=0;j<2;j++){ fileString += std::to_string(0); }
          fileString += std::to_string(i+1);
        }else if(i < 999){
          fileString += std::to_string(0);
          fileString += std::to_string(i+1);
        }else {
          fileString += std::to_string(i+1);
        }
        
        fileString += ".png";
        TYRA_LOG("Image: ", fileString); 
        const char* file = fileString.c_str();
        TYRA_LOG("Image const char: ", file); 
        sprite.push_back(new Sprite);
        spriteFrame.push_back(*sprite[sprite.size()-1]);
        LoadSprites(sprite[i], *position);
        LoadTextures(sprite[i], file);
        layer.push_back(0);
        fileString.clear();
  }

}

void Animation::LoadSprite(int spriteValue){
  firstFrame = 0;

  switch (spriteValue){
  case PeaShooterSingle:
    sprite = spr_PeaShooterSingle;
    for(int i=0; i<104;i++){
      spriteFrame.push_back(*sprite[i]);
      layer.push_back(0);
    }
      
      
    finalFrame = spr_PeaShooterSingle.size();
    break;
  
  default:
    break;
  }
}

void Animation::LoadSprite(int spriteValue,int initFrame,int lastFrame){

  firstImageFrame = initFrame;
  finalImageFrame = lastFrame;

  //firstFrame = initFrame;
  //finalFrame = lastFrame;
  firstFrame = 0;

  if(firstImageFrame > finalImageFrame - firstImageFrame){
    finalFrame = finalImageFrame - firstImageFrame + 1; 
  }else{
    finalFrame = finalImageFrame;
  }

  initFrame--; // como se incluye el primer frame, se resta
  int j = 0;
  switch (spriteValue){
  case PeaShooterSingle:
    
    for(int i=initFrame; i<lastFrame;i++){
      sprite.push_back(spr_PeaShooterSingle[i]);
      spriteFrame.push_back(*sprite[j]);
      layer.push_back(0);
      //printf("pos %d\n",j);
      //printf("sprite: %d\n",sprite[j]->id);
      //printf("frame: %d\n",spriteFrame[j]->id);
      j++;
    }
    break;
  
  default:
    break;
  }
}

// El frame que se ingresa empieza con 1 por el nombre de las imagenes
void Animation::SetInitialFrame(const unsigned int newFrame){ 
  if(newFrame == 0)
    firstFrame = newFrame;
  else
    firstFrame = newFrame-1; 
  frame = firstFrame; 
}

Sprite *Animation::GetSprite(int spritePos){
  return sprite[spritePos];
}

Sprite *Animation::NewSprite(){
  sprite.push_back(new Sprite);
  spriteFrame.push_back(*sprite[sprite.size()-1]);
  layer.push_back(0);
  //finalFrame = sprite.size();
  /*printf("new size anim: %u\n",sprite.size());
  printf("id sprite: %u\n",sprite[sprite.size()-1]->id);*/
  return sprite[sprite.size()-1];
}

Sprite Animation::LoopAnim(const unsigned int finalFrame) { 
    //TYRA_LOG("FPS: ", engine->info.getFps());
    //TYRA_LOG("Loop!"); 
    
    //printf("Position Animation: (%f,%f)\n", position->x ,position->y);
    if(timer > seconds){
      timer = 0;
      frame++;
      
      if(frame >= finalFrame || frame >= sprite.size()){
        frame = firstFrame;
      }
      //TYRA_LOG("frame: ",frame);
    }

    timer += timerTyra.getTimeDelta() * 0.001; // En milisegundos

    //printf("timer: %f\n",timer);

    timerTyra.prime();

    spriteFrame[frame].position = sprite[frame]->position + *position;
    return spriteFrame[frame];
}

Sprite Animation::LoopAnim(const unsigned int finalFrame, bool stopFrame, bool reverse) { 
    
    //printf("Position Animation: (%f,%f)\n", position->x ,position->y);
    if(stopFrame == false){
      if(timer > seconds){
        timer = 0;

        if(reverse == false)frame++;
        else                frame--;
        
        if(frame >= finalFrame || frame >= sprite.size()){
          if(frame )
          frame = firstFrame;
        }  
      }
    }
    TYRA_LOG("frame: ",frame);
    TYRA_LOG("sprite.size(): ",sprite.size());
    
    timer += timerTyra.getTimeDelta() * 0.001; // En milisegundos

    //printf("timer: %f\n",timer);

    timerTyra.prime();

    spriteFrame[frame].position = sprite[frame]->position + *position;
    return spriteFrame[frame];
}

Sprite Animation::LoopAnim(bool stopFrame, bool reverse) {    
    //printf("Position Animation: (%f,%f)\n", position->x ,position->y);
    if(stopFrame == false){
      if(timer > seconds){
        timer = 0;

        if(reverse == false)frame++;
        else                frame--;
        
        if(frame >= finalFrame || frame >= sprite.size()){
          frame = firstFrame;
        }  
      }
    }
    //TYRA_LOG("frame: ",frame);
    
    timer += timerTyra.getTimeDelta() * 0.001; // En milisegundos

    //printf("timer: %f\n",timer);

    timerTyra.prime();

    spriteFrame[frame] = *sprite[frame];
    spriteFrame[frame].position = sprite[frame]->position + *position;
    //printf("%f,%f\n",spriteFrame[frame].position.x,spriteFrame[frame].position.y );
    return spriteFrame[frame];
}

void Animation::SetSeconds(const float newSeconds){ seconds = newSeconds; }

// Use the frame inserted by the images numbers in the repository
// include the first frame and final frame set
void Animation::SetPositionFrameByImageFrame(unsigned int framePos, Vec2 newPos){ 

  if(framePos >= firstImageFrame && framePos <= finalImageFrame)  
  {
    int newFrame = framePos - firstImageFrame;
    //printf("%d = %d-%d\n",newFrame,framePos,firstImageFrame);
    sprite[newFrame]->position = newPos;
  }
  else TYRA_WARN("FRAME OF THE POSITION DON'T EXIST, CHANGE THE POSITION");
}

// Use Frames to 0 to the final frame
void Animation::SetPositionFrameBySpriteSize(unsigned int frame, Vec2 newPos){
  if(frame < sprite.size()){ sprite[frame]->position = newPos; }
} 

Vec2 Animation::GetPositionFrame(const unsigned int frame){
  return sprite[frame]->position;
}

void Animation::SetFrameLayer(const int frame, const int newLayer){ 
  layer[frame] = newLayer;

  /*bool createLayer = false;
  for(unsigned int i = 0;i<totalLayers.size();i++){
    if(totalLayers[i] != newLayer){
      createLayer = true;
      i= totalLayers.size();
    }
  }

  if(createLayer){ 
    totalLayers.push_back(newLayer); 
    printf("new layer value: %d\n",newLayer);
    OrderLayers();
  }*/
}

Sprite* Animation::GetFrame(const int frame){ return &spriteFrame[frame];}

int Animation::GetFrameLayer(const int frame){
  return layer[frame];
}

void Animation::LoadSprites(Sprite* sprite, Vec2 newPosition) {
  sprite->mode = SpriteMode::MODE_STRETCH;

  sprite->size = Vec2(128.0F, 128.0F);

  sprite->position = newPosition;  

  TYRA_LOG("Sprite created!");
}

void Animation::LoadTextures(Sprite* sprite, const char* image) {
  /**
   * Renderer has high layer functions,
   * which allows to render:
   * - Sprite (2D)
   * - Mesh (3D)
   *
   * It uses ONLY low layer functions which are in renderer.core
   */
  auto& renderer = engine->renderer;

  /**
   * TextureRepository is a repository of textures.
   * It is a singleton class, with all game textures.
   * We are linking these textures with sprite's (2D) and mesh (3D) materials.
   */
  auto& textureRepository = renderer.getTextureRepository();
  /**
   * Texture is stored in "res" directory.
   * Content of "res" directory is automatically copied into
   * "bin" directory, which contains our final game.
   *
   * File utils automatically add's device prefix to the path,
   * based on current working directory.
   *
   * In PS2 world:
   * - USB has a "mass:" prefix
   * - Our PC in PS2Link has a "host:" prefix
   * - Our PC in PCSX2 has a "host:" prefix
   */
 
  auto filepath = FileUtils::fromCwd(image);
  TYRA_LOG("filepath ", filepath);
  /**
   * Tyra supports following PNG formats:
   * 32bpp (RGBA)
   * 24bpp (RGB)
   * 8bpp, palletized (RGBA)
   * 4bpp, palletized (RGBA)
   *
   * 8bpp and 4bpp are the fastest.
   * All of these formats can be easily exported via GIMP.
   */
  auto* texture = textureRepository.add(filepath);

  /** Let's assign this texture to sprite. */
  texture->addLink(sprite->id);

  TYRA_LOG("Texture loaded!");
}