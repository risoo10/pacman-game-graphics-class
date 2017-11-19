//
// Created by Riso on 11/11/2017.
//

#include "brick.h"
#include "scene.h"


#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;


// Shared resources
unique_ptr<Mesh> Brick::mesh;
unique_ptr<Texture> Brick::texture;
unique_ptr<Shader> Brick::shader;

Brick::Brick() {

    // Initialize static resources if needed
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("brick.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("cube.obj");

}

bool Brick::update(Scene &scene, float dt) {


    generateModelMatrix();
    return true;
}


void Brick::render(Scene &scene) {

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




