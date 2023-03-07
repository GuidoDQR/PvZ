#include "gameObject.hpp"

using namespace Tyra;

GameObjectManager GOmanager;

GameObjectManager::GameObjectManager(){}

GameObject::GameObject() : anim(camera.camera[0],&position,&sprite){
    //printf("pos gameobject: %f,%f\n",position.x,position.y);
    position.x = position.y = 0;
    layer = 0;
    GOmanager.Add(this);
}

void GameObjectManager::Add(GameObject* gameObject){
    gameObjects.push_back(gameObject);
}

void GameObjectManager::Render(){
    //printf("\n\nGameObjectManager\n");
    //printf("texture count: %u\n",camera.renderCamera()->renderer.getTextureRepository().getTexturesCount());
  
    Renderer2D* render2D = &camera.renderCamera()->renderer.renderer2D;
    Sprite spriteRender[gameObjects.size()];
    int layerRender[gameObjects.size()];

    // ordeno el orden de los GameObjects en base a su capa

    bool repeatGOLayer;
    do{
        repeatGOLayer = false;
        for(unsigned int i=0; i<gameObjects.size()-1;i++){
            if(gameObjects[i]->layer > gameObjects[i+1]->layer){
                GameObject* aux = gameObjects[i];
                gameObjects[i] = gameObjects[i+1];
                gameObjects[i+1] = aux;
                repeatGOLayer = true;
            }
        }
    }while(repeatGOLayer ==  true);
    //printf("GO size: %d\n",gameObjects.size());
    // obtengo el frame de la animacion del respectivo objeto

    int countSprite = 0;

    for(unsigned int i=0; i<gameObjects.size();i++){
        if(gameObjects[i]->anim.stopRender == false){
            if(gameObjects[i]->anim.SpriteSize() > 0){
                //printf("pos GO: %d\n",i);
                //printf("size anim: %u\n",gameObjects[i]->anim.SpriteSize());
                
                //printf("sprite id: %u\n",gameObjects[i]->anim.GetSprite(0)->id);
                //render2D->render(gameObjects[i]->anim.LoopAnim(gameObjects[i]->anim.stopFrame,gameObjects[i]->anim.reverseFrame));
                //printf("GO: %d, value: %d\n",i,gameObjects[i]->layer);
                spriteRender[countSprite] = gameObjects[i]->anim.LoopAnim(gameObjects[i]->anim.stopFrame,gameObjects[i]->anim.nextFrame,gameObjects[i]->anim.reverseFrame);
                layerRender [countSprite] = gameObjects[i]->anim.GetFrameLayer(gameObjects[i]->anim.GetActualFrame());
                //printf("id sprite: %u\n",spriteRender[countSprite].id);
                countSprite++;
            }
        }
    }

    //printf("count sprite: %d\n",countSprite);

    bool repeatOrderLayer;

    do{
        repeatOrderLayer = false; 
    //for(int i=0;i< totalLayers.size();i++){
        for(int j=0; j < countSprite-1;j++){
            if(layerRender[j+1] < layerRender[j]){
                int aux = layerRender[j+1];
                layerRender[j+1] = layerRender[j];
                layerRender[j] = aux;

                Sprite s_aux = spriteRender[j+1];
                spriteRender[j+1] = spriteRender[j];
                spriteRender[j] = s_aux;

                repeatOrderLayer = true;
            }
        }
    //}
    }while (repeatOrderLayer == true);

    for(int j=0; j < countSprite;j++){
        //printf("pos: %d\n",j);
        //printf("id sprite: %u\n",spriteRender[j].id);
        render2D->render(spriteRender[j]);     
    }
}
