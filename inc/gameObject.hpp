#pragma once

#include <tyra>
#include "animation.hpp"
#include "Camera.hpp"

class GameObject{
private:
    Camera camera;
public:
    GameObject();
    Tyra::Vec2 position;   
    Tyra::Vec2 size;    // width and height
    Animation anim;
    Tyra::Sprite* sprite;
    int layer;
};

class GameObjectManager{
private:
    Camera camera;
    std::vector<GameObject*> gameObjects;
    std::vector<GameObject*> renderGameObjects;
public:
    GameObjectManager();
    void Add(GameObject* gameObject);
    unsigned int Size();
    void Render();
};

inline unsigned int GameObjectManager::Size(){ return gameObjects.size(); }

extern GameObjectManager GOmanager; // Game Object manager
