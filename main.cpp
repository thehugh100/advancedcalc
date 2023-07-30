#include <inttypes.h>
#include <iostream>
#include <string_view>
#include <tuple>
#include <vector>
#include <stack>
#include <map>
#include <sstream>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Calculator.h"

#include <AAGL/Graphics.h>
#include <AAGL/Shape.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Font.h"

#include "Token.h"
#include "TokenList.h"
#include "CalcError.h"
#include "Functions.h"
#include "Instruction.h"

void runTests() {
    auto calculator = std::make_shared<Calculator>(false);

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
        {"((1+1))", 2.},
        {"+pi", M_PI},
        {"-pi - -pi", 0},
        {"sign(-pi)", -1},
    };

    int passes = 0;
    for(auto &i : testCases) {
        double result = calculator->calculateInput(i.first);
        if(result != i.second || !calculator->resultIsValid()) {
            std::cout << "Test case failed: '" << i.first << "', expected: " << i.second << ", got: " << result << std::endl;
            calculator->setDebug(true);
            calculator->calculateInput(i.first);
            calculator->setDebug(false);
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

    window = glfwCreateWindow(w, h, "Advanced Calculator", NULL, NULL);

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
    InputEngine(GLFWwindow* window) :buffer(""), window(window) {
        cursor = 0;
        lastInput = 0;
        calculator = new Calculator(false);
        result = 0;
        hasSuggestions = false;
        tokenStartOffset = 0;
        tokenEndOffset = 0;
        cursorDepth = 0;
        cursorPairDepth = -1;
        selectIndexEnd = 0;
        selectIndexStart = 0;
        hasSelectedText = false;
        parenthesisBalance = 0;
        lastInsertedChar = 0;
        resultInvalid = true;
    }

    void validateCursor() {
        cursor = std::max(0, cursor);
        cursor = std::min((int)(buffer.length()), cursor);

        cursorPairDepth = -1;

        int characterRunningCount = 0;
        for(auto &i : calculator->parsed->list) {
            if(cursor >= characterRunningCount && cursor <= characterRunningCount + i.getValue().length()) {
                cursorDepth = i.getDepth();
                if(cursorDepth != 0) {
                    cursorPairDepth = i.getPairId();
                }
                break;
            }
            characterRunningCount += i.getValue().length();
        }
    }

    void handleInput(unsigned int c) {
        resultInvalid = true;
        validateTextSelection();
        if(hasSelectedText) {
            buffer.erase(selectIndexStart, selectIndexEnd - selectIndexStart);
            cursor = selectIndexStart;
            resetTextSelection();
            validateCursor();
        }


        if(c == ')' && parenthesisBalance == 0 && lastInsertedChar == '(') {
            cursor++;
            validateCursor();
            checkBalance();
            lastInsertedChar = c;
            return;
        }

        if(cursor == buffer.length()) {
            buffer += c;
        } else {
            buffer = buffer.insert(cursor, 1, (char)c);
        }

        cursor++;

        if(c == '(' && parenthesisBalance == 0) {
            //buffer += ')';
            if(cursor == buffer.length()) {
                buffer += ')';
            } else {
                buffer = buffer.insert(cursor, 1, ')');
            }
        }

        lastInput = glfwGetTime();
        validateCursor();
        checkBalance();
        lastInsertedChar = c;
    }

    void handleBackspace() {
        validateTextSelection();
        if(hasSelectedText) {
            buffer.erase(selectIndexStart, selectIndexEnd - selectIndexStart);
            cursor = selectIndexStart;
            resetTextSelection();
            validateCursor();
            return;
        }

        if(buffer.size() >= 1) {
            if(cursor == buffer.length()) {
                buffer.erase(buffer.length() - 1);
                cursor--;
                cursor = std::max(0, cursor);
            } else {
                if(cursor != 0) {
                    int eraseLoc = std::max(cursor-1, 0);
                    char deleted = buffer[eraseLoc];
                    buffer.erase(eraseLoc, 1);
                    cursor--;
                    cursor = std::max(0, cursor);

                    checkBalance();
                    if(deleted == '(' && parenthesisBalance == -1) {
                        if(buffer.length() > eraseLoc && buffer[eraseLoc] == ')') {
                            buffer.erase(eraseLoc, 1);
                        }
                    }
                }
            }
        }

        validateCursor();
        checkBalance();
    }

    void startTextSelection() {
        selectIndexStart = cursor;
        selectIndexEnd = cursor;
        hasSelectedText = true;
    }

    void validateTextSelection() {
        int oStart = selectIndexStart;
        int oEnd = selectIndexEnd;
        selectIndexStart = std::max(0, std::min(oStart, oEnd));
        selectIndexEnd = std::min(std::max(oStart, oEnd), (int)buffer.length());
    }

    void resetTextSelection() {
        hasSelectedText = false;
    }

    void handleControl(int key, int scancode, int action, int mods) {
        resultInvalid = true;
        if(key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS) {
            //std::cout << "start text selection" << std::endl;
            startTextSelection();
        }
        if(key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE) {
            //std::cout << "end text selection" << std::endl;
            validateTextSelection();
        }


        if(action == GLFW_PRESS || action == GLFW_REPEAT) {
            if(key == GLFW_KEY_C && mods == GLFW_MOD_SUPER) {
                if(hasSelectedText) {
                    validateTextSelection();
                    std::string selectedText = buffer.substr(selectIndexStart, selectIndexEnd - selectIndexStart);
                    glfwSetClipboardString(window, selectedText.c_str());
                }
            }

            if(key == GLFW_KEY_V && mods == GLFW_MOD_SUPER) {
                const char* clipboardText = glfwGetClipboardString(window);
                if(clipboardText != nullptr) {
                    for(int i = 0; i < strlen(clipboardText); i++) {
                        handleInput(clipboardText[i]);
                    }
                }
            }

            if(key == GLFW_KEY_X && mods == GLFW_MOD_SUPER) {
                if(hasSelectedText) {
                    validateTextSelection();
                    std::string selectedText = buffer.substr(selectIndexStart, selectIndexEnd - selectIndexStart);
                    glfwSetClipboardString(window, selectedText.c_str());
                    handleBackspace();
                }
            }

            if(key == GLFW_KEY_A && mods == GLFW_MOD_SUPER) {
                selectIndexStart = 0;
                selectIndexEnd = buffer.length();
                hasSelectedText = true;
            }

            if(key == GLFW_KEY_BACKSPACE) {
                handleBackspace();
            }

            if(key == GLFW_KEY_DOWN) {
                if(hasSuggestions) {
                    suggestionsCursor++;
                    suggestionsCursor = std::min((int)(suggestions.size() - 1), suggestionsCursor);
                }
            }

            if(key == GLFW_KEY_UP) {
                if(hasSuggestions) {
                    suggestionsCursor--;
                    suggestionsCursor = std::max(0, suggestionsCursor);
                }
            }

            if(key == GLFW_KEY_TAB) {
                if(hasSuggestions) {
                    int suggestionWidth = tokenEndOffset - tokenStartOffset;
                    buffer.erase(tokenStartOffset, suggestionWidth);
                    cursor = tokenStartOffset;
                    if(suggestionsCursor < suggestions.size()) {
                        buffer = buffer.insert(cursor, suggestions[suggestionsCursor]);
                        cursor += suggestions[suggestionsCursor].length();
                    }
                    resetSuggestions();
                }
            }

            if(key == GLFW_KEY_LEFT) {
                if(mods == GLFW_MOD_SUPER) {
                    cursor = 0;
                } else if(mods == GLFW_MOD_SHIFT) {
                    cursor--;
                    selectIndexEnd = std::max(0, cursor);
                } else if(mods == (GLFW_MOD_SUPER | GLFW_MOD_SHIFT)) {
                    cursor = 0;
                    selectIndexEnd = std::max(0, cursor);
                } else {
                    if(hasSelectedText) {
                        resetTextSelection();
                        cursor = selectIndexStart;
                    } else {
                        cursor--;
                    }
                }

                cursor = std::max(0, cursor);
            }
            if(key == GLFW_KEY_RIGHT) {
                if(mods == GLFW_MOD_SUPER) {
                    cursor = buffer.length();
                } else if(mods == GLFW_MOD_SHIFT) {
                    cursor++;
                    selectIndexEnd = std::min((int)(buffer.length()), cursor);
                } else if(mods == (GLFW_MOD_SUPER | GLFW_MOD_SHIFT)) {
                    cursor = buffer.length();
                    selectIndexEnd = std::min((int)(buffer.length()), cursor);
                } else {
                    if(hasSelectedText) {
                        resetTextSelection();
                        cursor = selectIndexEnd;
                    } else {
                        cursor++;
                    }
                }

                cursor = std::min((int)(buffer.length()), cursor);
                checkBalance();
            }
        }
        lastInput = glfwGetTime();
        validateCursor();
    }

    static void charCallbackStatic(GLFWwindow* window, unsigned int codepoint) {
        InputEngine* instance = static_cast<InputEngine*>(glfwGetWindowUserPointer(window));
        instance->handleInput(codepoint);
    }

    static void keyCallbackStatic(GLFWwindow* window, int key, int scancode, int action, int mods) {
        InputEngine* instance = static_cast<InputEngine*>(glfwGetWindowUserPointer(window));
        instance->handleControl(key, scancode, action, mods);
    }

    std::vector<std::string> getSuggestions() {
        return suggestions;
    }

    void resetSuggestions() {
        suggestions.clear();
        suggestionsCursor = 0;
    }

    void checkBalance() {
        parenthesisBalance = 0;
        for(auto &i : buffer) {
            if(i == '(') {
                parenthesisBalance++;
            } else if(i == ')') {
                parenthesisBalance--;
            }
        }
    }

    void tick() {
        if(resultInvalid) {
            calculator->calculateInput(buffer); //bad way to error check
            if(calculator->resultIsValid()) {
                calculator->compileInput(buffer);
                result = calculator->executeInstructions();
            } else {
                result = 0;
            }
        }
        
        // std::cout << calculator->resultIsValid() << std::endl;

        int characterRunningCount = 0;
        hasSuggestions = false;
        for(auto &i : calculator->parsed->list) {
            if(i.isType(Token::TOKEN_IDENTIFIER) && !i.isResolved()) {
                if(cursor >= characterRunningCount && cursor <= characterRunningCount + i.getValue().length()) {
                    suggestions = calculator->getSuggestions(i.getValue());
                    if(suggestions.size() > 0) {
                        hasSuggestions = true;
                        tokenStartOffset = characterRunningCount;
                        tokenEndOffset = characterRunningCount + i.getValue().length();
                        break;
                    }
                }
            }
            characterRunningCount += i.getValue().length();
        }

        if(!hasSuggestions) {
            resetSuggestions();
        }
    }

    double getResult() {
        return result;
    }

    double result;
    int suggestionsCursor = 0;
    int cursor;
    std::string buffer;
    float lastInput;
    Calculator *calculator;
    int tokenStartOffset;
    int tokenEndOffset;
    std::vector<std::string> suggestions;
    bool hasSuggestions;
    int cursorDepth;
    int cursorPairDepth;

    int parenthesisBalance = 0;

    int selectIndexEnd = 0;
    int selectIndexStart = 0;
    int hasSelectedText = false;

    char lastInsertedChar = 0;
    bool resultInvalid;
    GLFWwindow* window;
};

glm::mat4 quadMat(float x, float y, float w, float h) {
    glm::mat4 mat = glm::mat4(1.0f);
    mat = glm::translate(mat, glm::vec3(x, y, 0.0f));
    mat = glm::scale(mat, glm::vec3(w, h, 1.0f));
    return mat;
}

int main() {
    runTests();
    float width = 1280;
    float height = 480;

    GLFWwindow* window = createWindow(width, height);
    if(!window) {
        exit(-1);
    }

    InputEngine* inputEngine = new InputEngine(window);
    
    glfwSetWindowUserPointer(window, inputEngine);
    glfwSetCharCallback(window, InputEngine::charCallbackStatic);
    glfwSetKeyCallback(window, InputEngine::keyCallbackStatic);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    // glEnable(GL_DEPTH_TEST);
    // glDepthFunc (GL_LESS);
    // glEnable(GL_CULL_FACE);

    glm::mat4 projection = glm::ortho(0.f, width, height, 0.f, -0.1f, 0.1f);

    Graphics* graphics = new Graphics("assets/");
    SDFFont* sdfFont12 = new SDFFont(graphics, "fonts/RobotoMono-Regular_22.json");
    
    Shape* selectRect = new Shape(graphics, graphics->findMesh("tlquad"));
    selectRect->col = glm::vec4(32., 145., 121., 255.) / glm::vec4(255.);

    Shape* hintRect = new Shape(graphics, graphics->findMesh("tlquad"));
    hintRect->col = glm::vec4(255., 255., 255., 32.) / glm::vec4(255.);

    sdfFont12->setProjectionMatrix(projection);

    glClearColor(0.05, 0.05, 0.05, 1.0);

    while (!glfwWindowShouldClose(window)) {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            inputEngine->calculator->setDebug(true);
            inputEngine->calculator->calculateInput(inputEngine->buffer);
            glfwSetWindowShouldClose(window, true);
            break;
        }

        float time = glfwGetTime();
        glClear(GL_COLOR_BUFFER_BIT);

        inputEngine->tick();
        double result = inputEngine->getResult();

        glm::vec3 position = glm::vec3(6., 22., 0.);
        glm::vec3 origPos = position;

        bool showErrors = true;

        if(inputEngine->hasSelectedText) {
            selectRect->view = quadMat(origPos.x + inputEngine->selectIndexStart * sdfFont12->getMonospaceAdvance(), origPos.y - 18., sdfFont12->getMonospaceAdvance() * (inputEngine->selectIndexEnd - inputEngine->selectIndexStart), 22.);
            selectRect->render(projection);
        }

        int characterRunningCount = 0;
        for(auto &i : inputEngine->calculator->parsed->list) {
            if (i.isParenthesis() && i.getPairId() == inputEngine->cursorPairDepth) {
                hintRect->view = quadMat(origPos.x + characterRunningCount * sdfFont12->getMonospaceAdvance(), origPos.y - 18., sdfFont12->getMonospaceAdvance(), 22.);
                hintRect->render(projection);
            }

            float w = 0;
            sdfFont12->renderTextSimple(
                position,
                i.getColor(), 
                i.getValue(),
                w,
                (i.isParenthesis() && i.getPairId() == inputEngine->cursorPairDepth) ? 0.97 : 1,
                0
            );
            position.x += w;
            characterRunningCount += i.getValue().length();
        }

        bool cursorState = (sin(time * 5.) > 0.) || ((glfwGetTime() - inputEngine->lastInput) < .25);

        float q = 0;
        sdfFont12->renderTextSimple(
            origPos + glm::vec3((sdfFont12->getMonospaceAdvance() * inputEngine->cursor) - sdfFont12->getMonospaceAdvance() * .5, 0., 0.), 
            glm::vec4(1., 1., 1., cursorState > 0. ? 1. : 0.05), 
            "|",
            q,
            1,
            0
        );

        if(inputEngine->calculator->resultIsValid()) {
            std::ostringstream resultStream;

            resultStream << " = ";
            if(result == (int)result) {
                resultStream << (int)result;
            } else {
                resultStream << std::setprecision(std::numeric_limits<double>::digits10) << result;
            }

            float w = 0;
            sdfFont12->renderTextSimple(
                position, 
                glm::vec4(.8, .8, .8, 1.), 
                resultStream.str(),
                w,
                1,
                0
            );
        } else {
            if(inputEngine->buffer.length() > 0 && !inputEngine->hasSuggestions) {
                auto errors = inputEngine->calculator->getErrors();
                glm::vec3 position = origPos + glm::vec3(0., 22., 0.);
                for(const auto &i : *errors) {
                    float w = 0;
                    sdfFont12->renderTextSimple(
                        position, 
                        i->getToken().getColor(), 
                        i->getToken().getValue(),
                        w,
                        1,
                        0
                    );
                    sdfFont12->renderTextSimple(
                        position + glm::vec3(w + sdfFont12->getMonospaceAdvance(), 0., 0.), 
                        glm::vec4(.8, .8, .8, 1.), 
                        i->getMessage(),
                        w,
                        1,
                        0
                    );
                    position += glm::vec3(0., 22., 0.);
                }
            }
        }

        if(inputEngine->hasSuggestions) {
            float yOff = 22;
            auto suggestions = inputEngine->getSuggestions();
            int index = 0;
            for(auto &s : suggestions) {
                showErrors = false;
                float lq = 0;

                if(inputEngine->suggestionsCursor == index) {
                    selectRect->view = quadMat(
                        origPos.x + (sdfFont12->getMonospaceAdvance() * inputEngine->tokenStartOffset), 
                        22. + yOff - 18., 
                        sdfFont12->getMonospaceAdvance() * s.length(), 
                        22.
                    );
                    selectRect->render(projection);
                }

                sdfFont12->renderTextSimple(
                    origPos + glm::vec3((sdfFont12->getMonospaceAdvance() * (inputEngine->tokenStartOffset)), yOff, 0.), 
                    glm::vec4(.8, .8, .8, 1.), 
                    s,
                    lq,
                    1,
                    0
                );

                yOff += 22;
                index++;
            }
        }

        float yOff = 100;
        for(auto &i : inputEngine->calculator->compiledInstructions) {
            float lq = 0;
            sdfFont12->renderTextSimple(
                origPos + glm::vec3(640, yOff, 0.), 
                glm::vec4(.8, .8, .8, 1.),
                i.toString(),
                lq,
                1,
                0
            );
            yOff += 22;
        }

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