//
// Created by Riso on 11/13/2017.
//

#include "food.h"
#include "scene.h"


#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;


// Shared resources
unique_ptr<Mesh> Food::mesh;
unique_ptr<Texture> Food::texture;
unique_ptr<Shader> Food::shader;

Food::Food() {

    // Initialize static resources if needed
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("pineapple.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("Pineapple.obj");

    scale = vec3{0.15f, 0.15f, 0.15f};
}

bool Food::update(Scene &scene, float dt) {

    if(eaten){
        return false;
    }

    bounce += dt * 200;
    if(bounce >= 360.0f){
        bounce = 0;
    }

    position.y = 0.1f + 0.15f * sin((PI / 180.0f) * bounce);
    rotation.z += dt;

    generateModelMatrix();
    return true;
}


void Food::render(Scene &scene) {

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