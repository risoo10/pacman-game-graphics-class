//
// Created by Riso on 11/20/2017.
//

#ifndef PPGSO_GHOST_H
#define PPGSO_GHOST_H


#include <ppgso.h>
#include "object.h"

class Ghost final : public ObjectRen {

private:
    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;

    float const fastSpeed = 0.004;
    float const slowSpeed = 0.001;

    float speed = fastSpeed;

    float maxBoozedAge = 3;

    glm::vec2 newDirection = {0,0};
    glm::vec3 movement = {0,0,0};


public:

    // Ghost state
    bool boozed = false;
    bool eaten = false;

    float boozedAge = 0;


    // Create new Brick
    Ghost();

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

};


#endif //PPGSO_GHOST_H
