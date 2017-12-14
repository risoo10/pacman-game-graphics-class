//
// Created by Riso on 11/27/2017.
//

#ifndef PPGSO_Z_H
#define PPGSO_Z_H

#include <ppgso.h>
#include "object.h"


class Zzz final : public ObjectRen {

private:
    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;


public:

    // Set as eaten
    bool eaten = false;

    float time = 0;

    int index;

    // Create new Brick
    Zzz();

    /*!
   * Update player position considering keyboard inputs
   * @param scene Scene to update
   * @param dt Time delta
   * @return true to delete the object
   */
    bool update(Scene &scene, float dt, glm::vec3 position);

    bool update(Scene &scene, float dt) override ;

    /*!
     * Render player
     * @param scene Scene to render in
     */
    void render(Scene &scene) override;

};


#endif //PPGSO_Z_H
