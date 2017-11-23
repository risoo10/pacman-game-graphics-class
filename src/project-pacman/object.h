#pragma once
#include <memory>
#include <list>
#include <map>

#include <glm/glm.hpp>

// Forward declare a scene
class Scene;

/*!
 *  Abstract scene object interface
 *  All objects in the scene should be able to update and render
 *  Generally we also want to keep position, rotation and scale for each object to generate a modelMatrix
 */
class ObjectRen {
public:
    // Define default constructors as this is an abstract class
    ObjectRen() = default;
    ObjectRen(const ObjectRen&) = default;
    ObjectRen(ObjectRen&&) = default;
    virtual ~ObjectRen() {};

  /*!
   * Update Object parameters, usually used to update the modelMatrix based on position, scale and rotation
   *
   * @param scene - Reference to the Scene the object is rendered in
   * @param dt - Time delta for animation purposes
   * @return true to delete the object
   */
  virtual bool update(Scene &scene, float dt) = 0;

  /*!
   * Render the object in the scene
   * @param scene
   */
  virtual void render(Scene &scene) = 0;

  // Object properties
  glm::vec3 position{0,0,0};
  glm::vec3 rotation{0,0,0};
  glm::vec3 scale{1,1,1};
  glm::mat4 modelMatrix{1};

protected:
  /*!
   * Generate modelMatrix from position, rotation and scale
   */
    void generateModelMatrix();

    bool possibleMove(glm::vec2 direction, glm::vec3 position, Scene &scene);

    bool oppositeDirection(glm::vec2 next, glm::vec2 actual);

    bool inTheMiddle(glm::vec3 position);

};

