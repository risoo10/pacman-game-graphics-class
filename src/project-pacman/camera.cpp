#include <glm/glm.hpp>

#include "camera.h"

using namespace std;
using namespace glm;
using namespace ppgso;

Camera::Camera(float fow, float ratio, float near, float far) {
  float fowInRad = (PI/180.0f) * fow;
  position.y = 18;
  position.z = 10.0f;


  projectionMatrix = perspective(fowInRad, ratio, near, far);
}

void Camera::update(std::map<int, int> keyboard, float dt){

//    if(keyboard[GLFW_KEY_LEFT]){
//      position.x -= dt;
//      focusOn.x -= dt;
//    }
//    if(keyboard[GLFW_KEY_RIGHT]){
//      position.x += dt;
//      focusOn.x += dt;
//    }
//    if(keyboard[GLFW_KEY_UP]){
//        position.z -= dt;
//        focusOn.z -= dt;
//    }
//    if(keyboard[GLFW_KEY_DOWN]){
//        position.z += dt;
//        focusOn.z += dt;
//    }

  viewMatrix = lookAt(position, focusOn, up);
}
