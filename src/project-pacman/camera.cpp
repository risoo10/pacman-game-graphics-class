#include <glm/glm.hpp>

#include "camera.h"

using namespace std;
using namespace glm;
using namespace ppgso;

Camera::Camera(float fow, float ratio, float near, float far) {
  float fowInRad = (PI/180.0f) * fow;
  projectionMatrix = perspective(fowInRad, ratio, near, far);
}

void Camera::update(std::map<int, int> keyboard, float dt, glm::vec3 pacmanPosition){

    // Change camera mode if pressed
    if(keyboard[GLFW_KEY_0]){
        cameraMod = 0;
    } else if(keyboard[GLFW_KEY_1]){
        cameraMod = 1;
    }


    if(cameraMod == 0) {

        position.y = 12;

        position.x = 0 + pacmanPosition.x * 0.3;
        position.z = 6.0f + pacmanPosition.z * 0.3;

        focusOn.x = 0 + pacmanPosition.x * 0.3;
        focusOn.z = 0 + pacmanPosition.z * 0.3;
    } else if(cameraMod == 1){

        position.y = 18;
        position.x = 0;
        position.z = 0.2;

        focusOn.x = 0;
        focusOn.z = 0;
        focusOn.y = 0;

    }

    viewMatrix = lookAt(position, focusOn, up);
}
