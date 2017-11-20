//
// Created by Riso on 11/11/2017.
//

#include "pacman.h"
#include "food.h"
#include "scene.h"
#include "math.h"
#include "ghost.h"
#include "drink.h"

#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>
#include <src/gl9_scene/explosion.h>

using namespace std;
using namespace glm;
using namespace ppgso;


// Shared resources
unique_ptr<Mesh> Pacman::mesh;
unique_ptr<Texture> Pacman::texture;
unique_ptr<Shader> Pacman::shader;


// Constructor
Pacman::Pacman() {

    // Initialize static resources if needed
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("sphere.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("sphere.obj");

    position.y = 0.2;

}

// Returns true if position of the object is near the middle of coordinates
bool inTheMiddle(vec3 position){

    // If in the middle
    if(fmod(position.x, 1.0f) == 0 && fmod(position.z, 1.0f) == 0){
        return true;
    }

    return false;
}

bool oppositeDirection(vec2 next, vec2 actual){

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

bool possibleMove(vec2 direction, vec3 position, Scene &scene){

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


// Update function
bool Pacman::update(Scene &scene, float dt) {

    // Hit detection
    for ( auto& obj : scene.objects ) {

        // Detect eaten food
        auto food = dynamic_cast<Food*>(obj.get());
        if (food){

            if (distance(position, food->position) < 0.4f) {

                // Set foot as eaten
                food->eaten = true;
                eatenFood++;
            }

        } else {

            // Detect drink
            auto drink = dynamic_cast<Drink*>(obj.get());
            if (drink){




            } else {

                // Detect Ghost
                auto ghost = dynamic_cast<Ghost*>(obj.get());
                if (ghost){

                    if(distance(position, food->position) < 0.4f){

                        if(ghost->boozed){
                            ghost->eaten = true;
                        } else {
                            // Game over
                            return false;
                        }
                    }

                } else {
                    continue;
                }
            }
        }
    }

    // Proces next directions
    if (scene.keyboard[GLFW_KEY_RIGHT]){ // Right
        nextDirection.x = 1;
        nextDirection.y = 0;
    } else if (scene.keyboard[GLFW_KEY_LEFT]){ // Left
        nextDirection.x = -1;
        nextDirection.y = 0;
    } else if (scene.keyboard[GLFW_KEY_UP]){ // Up
        nextDirection.x = 0;
        nextDirection.y = 1;
    } else if (scene.keyboard[GLFW_KEY_DOWN]){ // Down
        nextDirection.x = 0;
        nextDirection.y = -1;
    }

    // Check if pacman is in the middle or if user choosen the opposite direction then actual
    if(inTheMiddle(position) || oppositeDirection(nextDirection, direction)){

        // Check if there is next direction and if it is possible to move in the new direction
        if(possibleMove(nextDirection, position, scene)){
            direction = nextDirection;

            // reset next direction
            nextDirection.x = 0;
            nextDirection.y = 0;

            // Create movement if is not paused
            if(dt){
                movement = vec3{direction.x * speed, 0, direction.y * speed * -1};
            } else {
                movement = vec3{0, 0, 0};
            }

        // Check the current direction if it is possible to move
        } else if(possibleMove(direction, position, scene)){

            // Create movement if not paused
            if(dt){
                movement = vec3{direction.x * speed, 0, direction.y * speed * -1};
            } else {
                movement = vec3{0, 0, 0};
            }
        } else {

            movement = vec3{0, 0, 0};

        }
    }

    //movement = vec3{nextDirection.x * speed, 0, nextDirection.y * speed * -1};

    // Update position by movement
    position += movement;
    position.x = (float)(round(position.x * 1000) / 1000.0); // Round to 3 decimal plates
    position.z = (float)(round(position.z * 1000) / 1000.0); // Round to 3 decimal plates

    generateModelMatrix();

    return true;
}


// Render function
void Pacman::render(Scene &scene) {

    shader->use();

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();

}


glm::vec3 Pacman::getPosition(){
    return position;
}





