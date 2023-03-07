#pragma once

#include <tyra>
#include <iostream>
#include "textures.hpp"

//extern std::vector<int> totalLayers;    // count the max layers used

void OrderLayers();

//La animacion puede tener varias estados con diferentes animaciones

class Animation{
private:
    Tyra::Engine* engine;
    Tyra::Timer timerTyra;
    Tyra::Vec2* position;    // Posicion del GameObject
    Tyra::Sprite** spriteGO; // Sprite of GameObject
    
    const char* image;
    int timer; 
    int frame;                     // Frame que se reproduce
    int firstFrame;                // Primer Frame que se reproduce
    int finalFrame;                // Ultimo Frame que se reproduce
    unsigned int firstImageFrame;  // Primer Frame basado en los numeros de la imagen 
    unsigned int finalImageFrame;  // Ultimo Frame basado en los numeros de la imagen 
    float seconds;
    
    std::vector<Tyra::Sprite*> sprite;      // sprite manipulado por el usuario
    
    std::vector<int>           layer;       // capa de renderizado  example: 0-first draw 10-last draw
public:
    Animation(); 
    Animation(Tyra::Engine* t_engine, Tyra::Vec2* gameObjectPosition, Tyra::Sprite** gameObjectSprite);
    ~Animation();
    std::vector<Tyra::Sprite>  spriteFrame; // sprite que sera renderizado 
    bool reverseFrame;
    bool stopFrame;
    bool stopRender;
    bool nextFrame;
    
    void SetRender(Tyra::Engine* engine);
    void SetPositionGameObject(Tyra::Vec2* position);
    
    void LoadSprite(SpritesTextures spriteValue,int initFrame,int lastFrame);
    unsigned int SpriteSize(); // function is down

    void SetInitialFrame(const unsigned int frame);
    Tyra::Sprite*GetSprite(int spritePos);
    Tyra::Sprite*NewSprite();
    Tyra::Sprite LoopAnim(bool stopFrame, bool nextFrame, bool reverse);

    void SetSeconds(const float seconds);
    void SetPositionFrameByImageFrame(unsigned int framePos, Tyra::Vec2 positions);
    void SetPositionFrameBySpriteSize(unsigned int frame, Tyra::Vec2 positions);
    Tyra::Vec2 GetPositionFrame(const unsigned int frame);

    void SetFrameLayer(const int frame, const int newLayer);
    int GetFrameLayer(const int frame);
    Tyra::Sprite* GetFrame(const int frame);
    unsigned int GetActualFrame();

    // tal vez sean innecesarios
    void SetImagePNG(const char* image, const int initialFrame, const int finalFrame);
    void LoadSprites(Tyra::Sprite* sprite, Tyra::Vec2 newPosition);
    void LoadSprites(Tyra::Sprite* sprite, Tyra::Vec2 newPosition, Tyra::Vec2 newSize);
    void LoadTextures(Tyra::Sprite* sprite, const char* image);

};

inline unsigned int Animation::SpriteSize(){ return sprite.size();}
inline unsigned int Animation::GetActualFrame(){ return frame; }