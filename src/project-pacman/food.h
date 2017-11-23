//
// Created by Riso on 11/13/2017.
//

#ifndef PPGSO_FOOD_H
#define PPGSO_FOOD_H


#include <ppgso.h>
#include "object.h"

class Food final : public ObjectRen {

private:
    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;


    // Dalsie parametre
    float bounce = 0;

public:

    // Set as eaten
    bool eaten = false;

    // Create new Brick
    Food();

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


#endif //PPGSO_FOOD_H
