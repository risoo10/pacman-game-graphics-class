//
// Created by Riso on 11/11/2017.
//

#ifndef PPGSO_PACMAN_H
#define PPGSO_PACMAN_H


#include <ppgso.h>
#include <queue>
#include "object.h"


// Keyframe animation
struct Keyframe {
    glm::vec3 keyPosition = {1, 1, 1}, keyRotation = {1, 1, 1}, keyScale = {1, 1, 1};
    float duration = 100;
};


class Pacman final : public ObjectRen {

private:
    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

    float const fastSpeed = 0.005;

    glm::vec2 direction = {0, 0};
    glm::vec2 nextDirection = {0, 0};
    glm::vec3 movement = {0, 0, 0};
    float speed = fastSpeed;

    bool gameWon = false;
    Keyframe endAnimation[5];
    int keyframeCount = 5;
    int processedKeyframes = 0;
    float animationDuration = 0;
    bool stopAnimation = false;

public:

    // Create new Pacman
    Pacman();





    /*!
   * Update player position considering keyboard inputs
   * @param scene Scene to update
   * @param dt Time delta
   * @return true to delete the object
   */
    bool update(Scene &scene, float dt) override;

    /*!
     * Render player
     * @param scene Scene to render in
     */
    void render(Scene &scene) override;





    glm::vec3 getPosition();

};


#endif //PPGSO_PACMAN_H
