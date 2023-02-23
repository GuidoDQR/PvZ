#include "Camera.hpp"

using namespace Tyra;

std::vector<Engine*> Camera::camera;
int Camera::cantCamera;

Camera::Camera(){
    if(cantCamera != 0){
        actualCamera = cantCamera; 
        showCamera = 0;
        cantCamera++;
    }else{
        TYRA_LOG("Camera don't exist, create one first");
    }
}

Camera::Camera(Engine* newCamera){
    actualCamera = cantCamera;
  
    /*TYRA_LOG("Camera actual pointer: ", newCamera);
    TYRA_LOG("Camera before pointer: ", camera[actualCamera-1]);*/
    if(newCamera != camera[actualCamera-1]){
        camera.push_back(newCamera);
        showCamera = actualCamera;
        TYRA_LOG("Camera ",actualCamera," created");
        //TYRA_LOG("Camera Created pointer: ", camera[actualCamera]);
        cantCamera++;
    }   
}

Tyra::Engine* Camera::renderCamera(){
    return camera[actualCamera];
}

void Camera::changeCamera(const int cam_pos){
    showCamera = cam_pos;
}