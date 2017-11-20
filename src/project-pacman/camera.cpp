#include <glm/glm.hpp>

#include "camera.h"

using namespace std;
using namespace glm;
using namespace ppgso;

Camera::Camera(float fow, float ratio, float near, float far) {
  float fowInRad = (PI/180.0f) * fow;
  position.y = 15;

  projectionMatrix = perspective(fowInRad, ratio, near, far);
}

void Camera::update(std::map<int, int> keyboard, float dt, glm::vec3 pacmanPosition){

    position.x = 0 + pacmanPosition.x * 0.3;
    position.z = 8.0f + pacmanPosition.z * 0.3;

    focusOn.x = 0 + pacmanPosition.x * 0.3;
    focusOn.z = 0 + pacmanPosition.z * 0.3;


  viewMatrix = lookAt(position, focusOn, up);
}
