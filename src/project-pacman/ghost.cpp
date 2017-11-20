//
// Created by Riso on 11/20/2017.
//

#include "ghost.h"
#include "scene.h"


#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;


// Shared resources
unique_ptr<Mesh> Ghost::mesh;
unique_ptr<Texture> Ghost::texture;
unique_ptr<Shader> Ghost::shader;

Ghost::Ghost() {

    // Initialize static resources if needed
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("pineapple.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("Pineapple.obj");

    scale = vec3{0.15f, 0.15f, 0.15f};
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


bool Ghost::update(Scene &scene, float dt) {


    // If eaten die
    if(eaten){
        return false;
    }

    // Random movement of the ghost
    if(inTheMiddle(position)){

        vec2 newDirection;

        do{
            int rand = linearRand(0, 3);
            switch (rand){
                case 0: // Right
                    newDirection.x = 1;
                    newDirection.y = 0;
                    break;
            }


        } while(possibleMove(newDirection, position, scene));

    }



    // Update position by movement
    position += movement;
    position.x = (float)(round(position.x * 1000) / 1000.0); // Round to 3 decimal plates
    position.z = (float)(round(position.z * 1000) / 1000.0); // Round to 3 decimal plates



    generateModelMatrix();
    return true;
}


void Ghost::render(Scene &scene) {

    shader->use();

    // Set up light
    shader->setUniform("LightDirection", scene.lightDirection);

    // use camera
    shader->setUniform("ProjectionMatrix", scene.camera->projectionMatrix);
    shader->setUniform("ViewMatrix", scene.camera->viewMatrix);

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();

}