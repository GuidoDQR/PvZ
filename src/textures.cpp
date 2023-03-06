#include "textures.hpp"
#include <fstream>
#include <iostream>

using namespace std;
using namespace Tyra;

std::vector<Sprite*> spr_PeaShooterSingle;

void LoadSprite(Sprite* sprite, Vec2 newPos, Vec2 newSize) {
  //const auto& screenSettings = engine->renderer.core.getSettings();
  sprite->mode = SpriteMode::MODE_STRETCH;

  // sprite->size = Vec2(80.0F, 80.0F);
  //  background size:(780.000000,524.000000)
  //  background position: (-85,0)
  sprite->size = newSize;
  //printf("Sprite Size: %f, %f\n", sprite->size.x, sprite->size.y);

  sprite->position = newPos;
  /*sprite->position = Vec2(screenSettings.getWidth()/ 2 - sprite->size.x / 2.0F
, screenSettings.getHeight() /2 - sprite->size.y / 2.0F );*/

  //TYRA_LOG("Sprite created!");
}

void LoadSprite(Sprite* sprite){
  sprite->mode = SpriteMode::MODE_STRETCH;

  sprite->size = Vec2(32,32);
  //printf("Sprite Size: %f, %f\n", sprite->size.x, sprite->size.y);

  sprite->position = Vec2(0,0);

  //TYRA_LOG("Sprite created!");
}

void LoadSprite(Sprite* sprite, Vec2 newPos, Vec2 newSize, SpriteMode mode) {
  //const auto& screenSettings = engine->renderer.core.getSettings();
  sprite->mode = mode;

  // sprite->size = Vec2(80.0F, 80.0F);
  //  background size:(780.000000,524.000000)
  //  background position: (-85,0)
  sprite->size = newSize;
  //printf("Sprite Size: %f, %f\n", sprite->size.x, sprite->size.y);

  sprite->position = newPos;
  /*sprite->position = Vec2(screenSettings.getWidth()/ 2 - sprite->size.x / 2.0F
, screenSettings.getHeight() /2 - sprite->size.y / 2.0F );*/

  //TYRA_LOG("Sprite created!");
}

void LoadTexture(Engine* engine, Sprite* sprite, const char* image) {
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

  //TYRA_LOG("Texture loaded!");
}

void LoadSprite(Sprite* sprite, Vec2 newPosition) {
  sprite->mode = SpriteMode::MODE_STRETCH;

  sprite->size = Vec2(128.0F, 128.0F);

  sprite->position = newPosition;  

  //TYRA_LOG("Sprite created!");
}

void LoadTexture(Sprite* sprite, const char* image, Engine* engine) {
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
  //TYRA_LOG("filepath ", filepath);
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
  //printf("sprite id en texture: %d\n",sprite->id);
  /** Let's assign this texture to sprite. */
  texture->addLink(sprite->id);

  //TYRA_LOG("Texture loaded!");
}


void Load_PeaShooter_Single_Sprites(Engine* engine){
  //TYRA_LOG("Setting Image"); 

  ifstream positions ("Animations/PeaShooterSingle/positions.txt");

  const char* image = "Animations/PeaShooterSingle/PeaShooterSingle";
  int frame = 0;
  int firstFrame = frame;
  int lastFrame = 104;
  std::string fileString;  
  Vec2 position;
  for(int i=firstFrame; i<lastFrame; i++){    
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
        //TYRA_LOG("Image: ", fileString); 
        const char* file = fileString.c_str();
        //TYRA_LOG("Image const char: ", file); 
        spr_PeaShooterSingle.push_back(new Sprite);
        positions >> position.x ;
        positions >> position.y ;
        LoadSprite(spr_PeaShooterSingle[i], position);
        LoadTexture(spr_PeaShooterSingle[i], file, engine);
        fileString.clear();
  }
}
