//
// Created by Riso on 11/14/2017.
//

#ifndef PPGSO_ENVIROMENT_H
#define PPGSO_ENVIROMENT_H


#include <ppgso.h>
#include "object.h"

class Enviroment final : public ObjectRen {

private:
    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;


    // Dalsie parametre

public:

    // Create new Brick
    Enviroment();

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

#endif //PPGSO_ENVIROMENT_H
