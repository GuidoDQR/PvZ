#include "miscellaneous.hpp"
#include "debugOptions.hpp"

Tyra::Sprite spr_box_collider;

bool Load_sprite_box_collider(Tyra::Engine* engine){
    LoadSprite(&spr_box_collider);
    if(spr_box_collider.size.x != 32 || spr_box_collider.size.y != 32){
        TYRA_WARN("ERROR SPRITE BOX COLLIDER NOT LOADED");
        return false;
    }

    LoadTexture(&spr_box_collider,"asset_box.png",engine);
    return true;
} 

bool ColliderCollision(Tyra::Sprite col1, Tyra::Sprite col2){
    if(col1.position.x + col1.size.x >= col2.position.x && 
       col1.position.y + col1.size.y >= col2.position.y &&
       col1.position.x <= (col2.position.x + col2.size.x) &&
       col1.position.y <= (col2.position.y + col2.size.y)){
        return true;
    }

    return false;
}

Box_collider::Box_collider(){ 
    sprite = spr_box_collider;
    sprite.color = Tyra::Color(0,255,0,128);
}

/*Box_collider::~Box_collider(){ 
   
}*/

Map::Map(){
    gameObject.anim.NewSprite();
    gameObject.anim.stopRender = true;
    Tyra::Sprite* newSprite = gameObject.anim.GetSprite(0);
    *newSprite = box.sprite;
    collider = newSprite;
    /*printf("map id sprite: %u\n",collider.sprite.id);
    printf("new map id sprite: %u\n",newSprite->id);
    printf("GO sprite ID: %u\n",gameObject.anim.GetFrame(0)->id);
    for(int i=0;i<10;i++){
        printf("Mira arriba\n");
    }*/
    //LoadSprite(newSprite,Tyra::Vec2(0,0),Tyra::Vec2(45,72));
    //gameObject.anim.GetNewSprite();  
    //gameObject.anim.LoadSprites(&collider.sprite,Tyra::Vec2(0,0),Tyra::Vec2(45,72));
    //gameObject.anim.SetPositionFrameBySpriteSize(0,gameObject.anim.GetSprite(0)->position);
}