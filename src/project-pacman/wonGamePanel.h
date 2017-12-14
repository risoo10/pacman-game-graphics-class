//
// Created by Riso on 12/11/2017.
//

#ifndef PPGSO_WONGAMEPANEL_H
#define PPGSO_WONGAMEPANEL_H


#include <ppgso.h>
#include "object.h"

class WonGamePanel final : public ObjectRen {

private:
    // Static resources (Shared between instances)
    static std::unique_ptr<ppgso::Mesh> mesh;
    static std::unique_ptr<ppgso::Shader> shader;
    static std::unique_ptr<ppgso::Texture> texture;


    // Dalsie parametre
    // Keyframe animation
    struct Keyframe {
        glm::vec3 keyPosition = {1, 1, 1}, keyRotation = {1, 1, 1}, keyScale = {1, 1, 1};
        float duration = 100;
    };

public:

    Keyframe endAnimation[2];
    int keyframeCount = 2;
    int processedKeyframes = 0;
    float animationDuration = 0;
    bool stopAnimation = false;

    // Create new Brick
    WonGamePanel();

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

#endif //PPGSO_WONGAMEPANEL_H
