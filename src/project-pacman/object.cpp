#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

#include "object.h"
#include "scene.h"

using namespace std;
using namespace glm;

void ObjectRen::generateModelMatrix() {
  modelMatrix =
          glm::translate(mat4(1.0f), position)
          * glm::orientate4(rotation)
          * glm::scale(mat4(1.0f), scale);
}

// Returns true if position of the object is near the middle of coordinates
bool ObjectRen::inTheMiddle(vec3 position){

  // If in the middle
  if(fmod(position.x, 1.0f) == 0 && fmod(position.z, 1.0f) == 0){
    return true;
  }

  return false;
}

bool ObjectRen::oppositeDirection(vec2 next, vec2 actual){

  // If next direction not set
  if(next.x == 0 && next.y == 0){
    return false;
  }

  // Right Left opposite
  if((next.x != actual.x && next.x + actual.x == 0) && next.y == actual.y){
    return true;
  }

  // Top Down opposite
  if((next.y != actual.y && next.y + actual.y == 0) && next.x == actual.x){
    return true;
  }

  return false;
}

bool ObjectRen::possibleMove(vec2 direction, vec3 position, Scene &scene){

  // Return if direction not set
  if(direction.x == 0 && direction.y == 0){
    return false;
  }

  // Map coordinates of the object to map coordinates
  int x = (int)(position.x + scene.mapRadius);
  int y = (int)(scene.mapRadius - position.z);

  // Check if it is the possible move
  if(scene.map[y + (int)direction.y][x + (int)direction.x] != 1){
    return true;
  }

  return false;
}

