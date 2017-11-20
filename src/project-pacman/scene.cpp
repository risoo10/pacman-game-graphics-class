#include "scene.h"

void Scene::update(float time) {

  // Update pacman
  if(!pacman->update(*this, time)){
    pacman = nullptr;
  }

  glm::vec3 newPacmanPosition = pacman == nullptr ? glm::vec3{0, 0, 0} : pacman->getPosition();

  // Update camera
  camera->update(keyboard, time, newPacmanPosition);


  // Use iterator to update all objects so we can remove while iterating
  auto i = std::begin(objects);

  while (i != std::end(objects)) {
    // Update and remove from list if needed
    auto obj = i->get();
    if (!obj->update(*this, time))
      i = objects.erase(i); // NOTE: no need to call destructors as we store shared pointers in the scene
    else
      ++i;
  }
}

void Scene::render() {

  // Simply render all objects
  for ( auto& obj : objects )
    obj->render(*this);

  // Render pacman
  if(pacman != nullptr){
    pacman->render(*this);
  }
}
