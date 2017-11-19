#ifndef _PPGSO_SCENE_H
#define _PPGSO_SCENE_H

#include <memory>
#include <map>
#include <list>

#include "object.h"
#include "camera.h"


/*
 * Scene is an object that will aggregate all scene related data
 * Objects are stored in a list of objects
 * Keyboard and Mouse states are stored in a map and struct
 */
class Scene {
  public:
    /*!
     * Update all objects in the scene
     * @param time
     */
    void update(float time);

    /*!
     * Render all objects in the scene
     */
    void render();

    // Camera object
    std::unique_ptr<Camera> camera;

    // Mapa pre hru
    // Create Map
    short map[11][11] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 2, 0, 0, 1, 1, 0, 0, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 3, 0, 0, 0, 2, 1},
            {1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 0, 2, 0, 1, 1, 1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };

    short mapRadius = 5;

    // All objects to be rendered in scene
    std::list< std::unique_ptr<Object> > objects;

    // Lights, in this case using only simple directional diffuse lighting
    glm::vec3 lightDirection{1.0f, 0.75f, 0.5f};

    // Keyboard state
    std::map< int, int > keyboard;

};

#endif // _PPGSO_SCENE_H
