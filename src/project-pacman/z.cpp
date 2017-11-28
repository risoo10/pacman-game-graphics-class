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

    this->position.x = position.x;
    this->position.z = position.z;

    rotation.z += dt;

    modelMatrix = translate(mat4(1.0f), this->position) *
            translate(mat4(1.0f), position) *
            orientate4(rotation) *
            translate(mat4(1.0f), -position) *
            glm::scale(mat4(1.0f), scale);


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
