//
// Created by Riso on 11/11/2017.
//

#include "floor.h"
#include "scene.h"


#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;


// Shared resources
unique_ptr<Mesh> Floor::mesh;
unique_ptr<Texture> Floor::texture;
unique_ptr<Shader> Floor::shader;

Floor::Floor() {

    // Initialize static resources if needed
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("floor.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("quad.obj");

    scale = vec3{5.0f, 5.0f, 5.0f};
    position.y = -0.5f;
    rotation.x = 270 * (PI / 180);
}


bool Floor::update(Scene &scene, float dt) {



    generateModelMatrix();
    return true;
}

void Floor::render(Scene &scene) {

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