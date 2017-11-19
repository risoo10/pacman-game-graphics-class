// Example gl_scene
// - Introduces the concept of a dynamic scene of objects
// - Uses abstract object interface for Update and Render steps
// - Creates a simple game scene with Player, Asteroid and Space objects
// - Contains a generator object that does not render but adds Asteroids to the scene
// - Some objects use shared resources and all object deallocations are handled automatically
// - Controls: LEFT, RIGHT, "R" to reset, SPACE to fire

#include <iostream>
#include <map>
#include <list>

#include <ppgso/ppgso.h>
#include "camera.h"
#include "scene.h"
#include "brick.h"
#include "floor.h"
#include "enviroment.h"
#include "food.h"
#include "drink.h"
#include "pacman.h"


using namespace std;
using namespace glm;
using namespace ppgso;

const unsigned int SIZEX = 1024;
const unsigned int SIZEY = 768;

/*!
 * Custom windows for our simple game
 */
class SceneWindow : public Window {
private:
    Scene scene;
    bool animate = true;

    /*!
     * Reset and initialize the game scene
     * Creating unique smart pointers to objects that are stored in the scene object list
     */
    void initScene() {
        scene.objects.clear();

        // Create a camera
        auto camera = make_unique<Camera>(40.0f, (float)SIZEX / (float)SIZEY, 0.1f, 100.0f);
        scene.camera = move(camera);

        // Create enviroment
        auto enviroment = make_unique<Enviroment>();
        scene.objects.push_back(move(enviroment));

        // Create floor
        auto floor = make_unique<Floor>();
        scene.objects.push_back(move(floor));

        // Create walls and food from MAP
        for(int y = 0; y < 11; y++){
            for(int x = 0; x < 11; x++) {

                if(scene.map[y][x] == 1){ // Walls if map is 1
                    auto brick1 = make_unique<Brick>();
                    brick1->position.z = (10 - y) - scene.mapRadius;
                    brick1->position.x = x - scene.mapRadius;
                    scene.objects.push_back(move(brick1));
                } else if(scene.map[y][x] == 0){  // Food if map is 0
                    auto food = make_unique<Food>();
                    food->position.z = (10 - y) - scene.mapRadius;
                    food->position.x = x - scene.mapRadius;
                    scene.objects.push_back(move(food));
                } else if(scene.map[y][x] == 2){ // Drink if map is 2
                    auto pepsi = make_unique<Drink>();
                    pepsi->position.z = (10 - y) - scene.mapRadius;
                    pepsi->position.x = x - scene.mapRadius;
                    scene.objects.push_back(move(pepsi));
                } else if(scene.map[y][x] == 3){ // Pacmaaaan if map is 3
                    auto pacman = make_unique<Pacman>();
                    pacman->position.z = (10 - y) - scene.mapRadius;
                    pacman->position.x = x - scene.mapRadius;
                    scene.objects.push_back(move(pacman));
                }
            }
        }

        // Create Ghosts

        // Create Food

        // Create Flashback

    }

public:
    /*!
     * Construct custom game window
     */
    SceneWindow() : Window{"Pacman - Mocak", SIZEX, SIZEY} {
        hideCursor();
        glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

        // Initialize OpenGL state
        // Enable Z-buffer
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        // Enable polygon culling
        glEnable(GL_CULL_FACE);
        glFrontFace(GL_CCW);
        glCullFace(GL_BACK);

        initScene();
    }

    /*!
     * Handles pressed key when the window is focused
     * @param key Key code of the key being pressed/released
     * @param scanCode Scan code of the key being pressed/released
     * @param action Action indicating the key state change
     * @param mods Additional modifiers to consider
     */
    void onKey(int key, int scanCode, int action, int mods) override {
        scene.keyboard[key] = action;

        // Reset
        if (key == GLFW_KEY_R && action == GLFW_PRESS) {
            initScene();
        }

        // Pause
        if (key == GLFW_KEY_P && action == GLFW_PRESS) {
            animate = !animate;
        }
    }


    /*!
     * Window update implementation that will be called automatically from pollEvents
     */
    void onIdle() override {
        // Track time
        static auto time = (float) glfwGetTime();

        // Compute time delta
        float dt = animate ? (float) glfwGetTime() - time : 0;

        time = (float) glfwGetTime();

        // Set gray background
        glClearColor(0.0f, 0.0f, 0.0f, 0);
        // Clear depth and color buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Update and render all objects
        scene.update(dt);
        scene.render();
    }
};

int main() {
    // Initialize our window
    SceneWindow window;

    // Main execution loop
    while (window.pollEvents()) {}

    return EXIT_SUCCESS;
}
