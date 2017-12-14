//
// Created by Riso on 11/20/2017.
//

#include "ghost.h"
#include "pacman.h"
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
    if (!texture) texture = make_unique<Texture>(image::loadBMP("ghost.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("ghost.obj");

    scale = vec3{0.08f, 0.08f, 0.08f};
}


bool Ghost::update(Scene &scene, float dt) {


    // If eaten die
    if(eaten){
        // Clear zzz objects
        zzzs.clear();
        return false;
    }

    // If boozed then slow
    if(boozed){
        // Boozed started
        if(boozedAge == 0){
            position.x = (float)(round(position.x * 10) / 10.0); // Round to 2 decimal plates
            position.z = (float)(round(position.z * 10) / 10.0);
        }

        // Create ZZZ objects
        if(zzzs.empty()){
            // Create Zzz
            for(int i = 1; i < 5; i++){
                auto zzz = make_unique<Zzz>();
                zzz->index = i;
                zzzs.push_back(move(zzz));
            }
        }


        boozedAge += 0.01;
        speed = slowSpeed;

        // End of boozing
        if(boozedAge > maxBoozedAge){
            zzzs.clear();
            boozed = false;
            boozedAge = 0;
            position.x = (float)(round(position.x * 10) / 10.0); // Round to 2 decimal plates
            position.z = (float)(round(position.z * 10) / 10.0);
            speed = fastSpeed;
        }

    } else {
        speed = fastSpeed;;
    }


    // Random movement of the ghost
    if(inTheMiddle(position) && (!possibleMove(newDirection, position, scene) || (int)(linearRand(0, 3)) == 0)){

        do{
            int rand = linearRand(0, 3);
            switch (rand){
                case 0: // Right
                    newDirection.x = 1;
                    newDirection.y = 0;
                    rotation.z = PI / 2;
                    break;
                case 1: // Left
                    newDirection.x = -1;
                    newDirection.y = 0;
                    rotation.z = 3 * PI / 2;
                    break;
                case 2: // Up
                    newDirection.x = 0;
                    newDirection.y = 1;
                    rotation.z = PI;
                    break;
                case 3: // Down
                    newDirection.x = 0;
                    newDirection.y = -1;
                    rotation.z = 0;
                    break;
            }

        } while(!possibleMove(newDirection, position, scene));

        movement = vec3{newDirection.x, 0, newDirection.y * -1};
    }

    // Update position by movement
    if(dt) {
        position += movement * speed;
    }

    // Round to 3 decimal plates for precise movement
    position.x = (float)(round(position.x * 1000) / 1000.0); // Round to 2 decimal plates
    position.z = (float)(round(position.z * 1000) / 1000.0); // Round to 2 decimal plates

    // Simply update all zzzs
    // They are clearred not by calling false on update
    for ( auto& obj : zzzs )
        obj->update(scene, dt, position);


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

    // Simply render all zzzs
    for ( auto& obj : zzzs )
        obj->render(scene);

}