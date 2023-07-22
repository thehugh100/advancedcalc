#include <inttypes.h>
#include <iostream>
#include <string_view>
#include <tuple>
#include <vector>
#include <stack>
#include <map>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Calculator.h"

#include <AAGL/Graphics.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Font.h"

void runTests() {
    Calculator calculator(false);
    const std::vector<std::pair<std::string, double>> testCases = {
        {"1+1", 2},
        {"1.5 + 1.5", 3},
        {"1.5 + -1.5", 0},
        {"-1 + -2 + (-1 * 2)", -5.0},
        {"0x0A + 10", 20},
        {"0xFF + -0x0F", 240},
        {"33-9+40-(30+15)", 19},
        {"TAU + PI + (-PI + -TAU)", 0.},
        {"max(1, max(1, 2))", 2.},
        {"((1+1))", 2.}
    };

    int passes = 0;
    for(auto &i : testCases) {
        double result = calculator.calculateInput(i.first);
        if(result != i.second) {
            std::cout << "Test case failed: '" << i.first << "', expected: " << i.second << ", got: " << result << std::endl;
            calculator.setDebug(true);
            calculator.calculateInput(i.first);
            calculator.setDebug(false);
        } else {
            passes++;
        }
    }
    std::cout << "Tests passed " << passes << "/" << testCases.size() << std::endl;
}

GLFWwindow* createWindow(float w, float h) {
    GLFWwindow* window;

    if (!glfwInit())
        return nullptr;

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, true);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);    
    //glfwWindowHint(GLFW_DECORATED, false);
    //glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);

    window = glfwCreateWindow(w, h, "test", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return nullptr;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
        int version = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    if (version == 0) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return nullptr;
    }

    return window;
}

class InputEngine {
    public:
    InputEngine() :buffer("") {
        cursor = 0;
    }

    void handleInput(unsigned int c) {
        if(cursor == buffer.length()) {
            buffer += c;
        } else {
            buffer = buffer.insert(cursor, 1, (char)c);
        }
        cursor++;

        std::cout << "Cursor: " << cursor << std::endl << "String: " << buffer.length() << std::endl;
    }

    void handleBackspace() {
        if(buffer.size() >= 1) {
            if(cursor == buffer.length()) {
                buffer.erase(buffer.length() - 1);
                cursor--;
                cursor = std::max(0, cursor);
            } else {
                if(cursor != 0) {
                    buffer.erase(std::max(cursor-1, 0), 1);
                    cursor--;
                    cursor = std::max(0, cursor);
                }
            }
        }
    }

    void handleControl(int key, int scancode, int action, int mods) {
        if(action == GLFW_PRESS || action == GLFW_REPEAT) {
            if(key == GLFW_KEY_BACKSPACE) {
                handleBackspace();
            }
            if(key == GLFW_KEY_LEFT) {
                cursor--;
                cursor = std::max(0, cursor);
            }
            if(key == GLFW_KEY_RIGHT) {
                cursor++;
                cursor = std::min((int)(buffer.length()), cursor);
            }
        }
    }

    static void charCallbackStatic(GLFWwindow* window, unsigned int codepoint) {
        InputEngine* instance = static_cast<InputEngine*>(glfwGetWindowUserPointer(window));
        instance->handleInput(codepoint);
    }

    static void keyCallbackStatic(GLFWwindow* window, int key, int scancode, int action, int mods) {
        InputEngine* instance = static_cast<InputEngine*>(glfwGetWindowUserPointer(window));
        instance->handleControl(key, scancode, action, mods);
    }

    int cursor;
    std::string buffer;
};

int main() {
    runTests();
    float width = 1280;
    float height = 480;

    GLFWwindow* window = createWindow(width, height);
    if(!window) {
        exit(-1);
    }

    InputEngine* inputEngine = new InputEngine();
    glfwSetWindowUserPointer(window, inputEngine);
    glfwSetCharCallback(window, InputEngine::charCallbackStatic);
    glfwSetKeyCallback(window, InputEngine::keyCallbackStatic);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    // glEnable(GL_DEPTH_TEST);
    // glDepthFunc (GL_LESS);
    // glEnable(GL_CULL_FACE);

    Graphics* graphics = new Graphics("assets/");
    SDFFont* sdfFont12 = new SDFFont(graphics, "fonts/RobotoMono-Regular_22.json");

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        sdfFont12->renderTextSimple(
            glm::ortho(0.f, width, height, 0.f, -0.1f, 0.1f), 
            glm::vec3(6., 22., 0.), 
            glm::vec3(1.), 
            inputEngine->buffer,
            1,
            0,
            inputEngine->cursor
        );

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    // Calculator calculator(true);
    // while(1) {
    //     std::cout << ">> ";
    //     std::string input = "";
    //     std::getline(std::cin, input);
    //     try {
    //         std::cout << calculator.calculateInput(input) << std::endl;
    //     } catch (std::runtime_error &e) {
    //         std::cout << e.what() << std::endl;
    //     }
    // }
}