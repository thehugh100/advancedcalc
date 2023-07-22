#pragma once

class Mesh;
class Shader;
class Graphics;

#include <map>
#include <filesystem>
#include <glm/glm.hpp>

struct FontChar {
    glm::vec4 atlasMetrics; //s, t, uvW, uvH
    glm::vec3 fontMetrics; //bearingX, bearingY, advance
    glm::mat4 model;
};

class SDFFont {
    public:
    void loadAtlas(std::filesystem::path path);
    void loadManifest(std::filesystem::path path);
    void renderTextSimple( 
        glm::mat4 projection, 
        glm::vec3 position, 
        glm::vec3 col, 
        std::string_view text, 
        float weight = 1.f, 
        float italics = 0.f,
        int cursorPos = -1
    );
    SDFFont(
        Graphics* graphics, 
        std::filesystem::path path
    );
    ~SDFFont();

    Mesh* mesh;
    Shader* shader;
    Graphics* graphics;
    unsigned int textureId;
    std::map<unsigned int, FontChar> atlasEntries;
    int atlasWidth;
    int atlasHeight;
    float size;
    float fontSize;
    float retinaScale;
};