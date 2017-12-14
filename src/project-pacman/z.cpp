//
// Created by Riso on 11/27/2017.
//

#include "z.h"
#include "scene.h"


#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>
#include <glm/gtx/euler_angles.hpp>

using namespace std;
using namespace glm;
using namespace ppgso;


// Shared resources
unique_ptr<Mesh> Zzz::mesh;
unique_ptr<Texture> Zzz::texture;
unique_ptr<Shader> Zzz::shader;

Zzz::Zzz() {

    // Initialize static resources if needed
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("bigz.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("bigz.obj");

    scale = vec3{0.02f, 0.02f, 0.02f};
    position.y = 1.1f;
}

bool Zzz::update(Scene &scene, float dt, vec3 position) {

    time += dt;
    int x,y;
    switch(index){
        case 1:
            x = 1;
            y = 1;
            break;
        case 2:
            x = -1;
            y = 1;
            break;
        case 3:
            x = 1;
            y = -1;
            break;
        case 4:
            x = -1;
            y = -1;
            break;
    }

    this->position.x = position.x + sin(time) * 0.7f * x;
    this->position.z = position.z + cos(time) * 0.7f * y;

    if(time > 2 * PI){
        time = 0;
    }

    generateModelMatrix();
    return true;
}

bool Zzz::update(Scene &scene, float dt) {

    return false;
}


void Zzz::render(Scene &scene) {

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
