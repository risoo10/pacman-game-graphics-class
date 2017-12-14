#ifndef _PPGSO_SCENE_H
#define _PPGSO_SCENE_H

#include <memory>
#include <map>
#include <list>

#include "object.h"
#include "camera.h"
#include "pacman.h"
#include "ghost.h"
#include "food.h"
#include "drink.h"
#include "wonGamePanel.h"


/*
 * Scene is an object that will aggregate all scene related data
 * Objects are stored in a list of objects
 * Keyboard and Mouse states are stored in a map and struct
 */
class Scene {
  public:

    bool animate = true;

    /*!
     * Update all objects in the scene
     * @param time
     */
    void update(float time);

    /*!
     * Render all objects in the scene
     */
    void render();

    void renderMap(int level);

    // Camera object
    std::unique_ptr<Camera> camera;

    // Mapa pre hru
    // Create Map

    int level = 1;

    bool switchLevel = false;

    bool gameWON = false;

    int maxFoods = 48;

    int eatenFood = 0;

    const short mapSize = 11;

    // 1 == WALL
    // 0 == FOOD
    // 2 == DRINK
    // 3 == PACMAN
    // 4 == GHOST SOURCE

    short map[11][11];

    short map1[11][11] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 2, 0, 0, 1, 1, 0, 0, 0, 4, 1},
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

    short map2[11][11] = {
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 3, 0, 0, 0, 0, 0, 0, 0, 2, 1},
            {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 1, 4, 0, 0, 0, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1},
            {1, 2, 0, 0, 0, 0, 0, 0, 0, 2, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    };


    short mapRadius = 5;

    // Ghosts
    std::list< std::unique_ptr<Ghost> > ghosts;

    // Foods
    std::list< std::unique_ptr<Food> > foods;

    // Drinks
    std::list< std::unique_ptr<Drink> > drinks;

    // Other objects
    std::list< std::unique_ptr<ObjectRen> > objects;

    // Pacman for delete
    std::list< std::unique_ptr<Pacman> > pacman;
    

    // Pacman position for camera
    glm::vec3 newPacmanPosition;



    // Lights, in this case using only simple directional diffuse lighting
    glm::vec3 lightDirection{1.0f, 0.75f, 0.5f};

    // Keyboard state
    std::map< int, int > keyboard;

};

#endif // _PPGSO_SCENE_H
