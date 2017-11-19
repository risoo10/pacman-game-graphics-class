//
// Created by Riso on 11/15/2017.
//

#ifndef PPGSO_DRINK_H
#define PPGSO_DRINK_H

#include <ppgso.h>
#include "object.h"

class Drink final : public Object {

private:
    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;


    // Dalsie parametre

public:

    // Create new Brick
    Drink();

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

#endif //PPGSO_DRINK_H
