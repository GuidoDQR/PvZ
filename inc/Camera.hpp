#pragma once
#include <tyra>
#include <iostream>

class Camera{
    static int cantCamera; // total  Cameras
    int actualCamera;      // Camera created
    int showCamera;        // Camera show in display
public:
    Camera();
    Camera(Tyra::Engine* newCamera);
    Tyra::Engine* renderCamera();
    void changeCamera(const int cam_pos);
    static std::vector<Tyra::Engine*> camera; // All the cameras have the same cameras
    Tyra::Vec2 position;
};
