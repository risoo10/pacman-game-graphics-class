//
// Created by Riso on 11/14/2017.
//

#include "enviroment.h"
#include "scene.h"


#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;


// Shared resources
unique_ptr<Mesh> Enviroment::mesh;
unique_ptr<Texture> Enviroment::texture;
unique_ptr<Shader> Enviroment::shader;

Enviroment::Enviroment() {

    // Initialize static resources if needed
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("enviroment.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("quad.obj");
}

bool Enviroment::update(Scene &scene, float dt) {


    generateModelMatrix();
    return true;
}


void Enviroment::render(Scene &scene) {

    // Disable writing to the depth buffer so we render a "background"
    glDepthMask(GL_FALSE);

    shader->use();

    // Set up light
    shader->setUniform("LightDirection", scene.lightDirection);

    // no 3D
    shader->setUniform("ViewMatrix", mat4{});
    shader->setUniform("ProjectionMatrix", mat4{});

    // render mesh
    shader->setUniform("ModelMatrix", modelMatrix);
    shader->setUniform("Texture", *texture);
    mesh->render();

    // Enable depth
    glDepthMask(GL_TRUE);

}
