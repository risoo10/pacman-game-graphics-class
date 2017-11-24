#include "scene.h"

void Scene::update(float time) {

  // Update pacman
  auto p = std::begin(pacman);



  while (p != std::end(pacman)) {
    // Update and remove from list if needed
    auto obj = p->get();
    if (!obj->update(*this, time))
      p = pacman.erase(p); // NOTE: no need to call destructors as we store shared pointers in the scene
    else
      newPacmanPosition = obj->position;
      ++p;
  }



  // Update camera
  camera->update(keyboard, time, newPacmanPosition);


  // Use iterator to update all objects so we can remove while iterating for basic objects
  auto i = std::begin(objects);

  while (i != std::end(objects)) {
    // Update and remove from list if needed
    auto obj = i->get();
    if (!obj->update(*this, time))
      i = objects.erase(i); // NOTE: no need to call destructors as we store shared pointers in the scene
    else
      ++i;
  }

  // Update for ghosts
  auto g = std::begin(ghosts);

  while (g != std::end(ghosts)) {
    // Update and remove from list if needed
    auto obj = g->get();
    if (!obj->update(*this, time))
      g = ghosts.erase(g); // NOTE: no need to call destructors as we store shared pointers in the scene
    else
      ++g;
  }

  // Update for foods
  auto f = std::begin(foods);

  while (f != std::end(foods)) {
    // Update and remove from list if needed
    auto obj = f->get();
    if (!obj->update(*this, time))
      f = foods.erase(f); // NOTE: no need to call destructors as we store shared pointers in the scene
    else
      ++f;
  }

  // Update for drinks
  auto d = std::begin(drinks);

  while (d != std::end(drinks)) {
    // Update and remove from list if needed
    auto obj = d->get();
    if (!obj->update(*this, time))
      d = drinks.erase(d); // NOTE: no need to call destructors as we store shared pointers in the scene
    else
      ++d;
  }

}

void Scene::render() {

  // Simply render all objects
  for ( auto& obj : objects )
    obj->render(*this);

  // Simply render all ghosts
  for ( auto& obj : ghosts )
    obj->render(*this);

  // Simply render all foods
  for ( auto& obj : foods )
    obj->render(*this);

  // Simply render all drinks
  for ( auto& obj : drinks )
    obj->render(*this);

  // Render pacman
  for ( auto& obj : pacman )
    obj->render(*this);
}
