//
// Created by Riso on 12/11/2017.
//

#include "wonGamePanel.h"
#include "scene.h"


#include <shaders/diffuse_vert_glsl.h>
#include <shaders/diffuse_frag_glsl.h>

using namespace std;
using namespace glm;
using namespace ppgso;


// Shared resources
unique_ptr<Mesh> WonGamePanel::mesh;
unique_ptr<Texture> WonGamePanel::texture;
unique_ptr<Shader> WonGamePanel::shader;

vec3 linearInterpolation(vec3 a, vec3 b, float t){
    vec3 result = (1 - t) * a + t * b;
    return result;
}


WonGamePanel::WonGamePanel() {

    // Initialize static resources if needed
    if (!shader) shader = make_unique<Shader>(diffuse_vert_glsl, diffuse_frag_glsl);
    if (!texture) texture = make_unique<Texture>(image::loadBMP("winner.bmp"));
    if (!mesh) mesh = make_unique<Mesh>("quad.obj");


    scale = vec3{0.5f, 0.6f, 1.0f};

    rotation.x = 0 * (PI / 180);

}


bool WonGamePanel::update(Scene &scene, float dt) {

    generateModelMatrix();
    return true;
}

void WonGamePanel::render(Scene &scene) {

    // Disable writing to the depth buffer so we render a "background"
    glDepthMask(GL_FALSE);

    shader->use();

    // Set up light
    shader->setUniform("LightDirection", vec3(1.0, 1.0, 1.0));

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