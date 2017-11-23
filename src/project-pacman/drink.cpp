//
// Created by Riso on 11/15/2017.
//

#include "drink.h"
#include "scene.h"


#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;


// Shared resources
unique_ptr<Mesh> Drink::mesh;
unique_ptr<Texture> Drink::texture;
unique_ptr<Shader> Drink::shader;

Drink::Drink() {

    // Initialize static resources if needed
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("explosion.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("cube.obj");

    scale = vec3{0.35f, 0.35f, 0.35f};

    position.y = 0.2f;
}

bool Drink::update(Scene &scene, float dt) {

    if(drinked){
        return false;
    }

    rotation.z += dt;

    generateModelMatrix();

    return true;
}


void Drink::render(Scene &scene) {

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