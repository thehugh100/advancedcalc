#include "Font.h"
#include <iostream>
#include <glad/glad.h>

#include <AAGL/Mesh.h>
#include <AAGL/Shader.h>
#include <AAGL/Graphics.h>
#include <AAGL/AssetFilesystem.h>
#include <glm/ext.hpp>

#include <stb_image.h>

#include <nlohmann/json.hpp>

void SDFFont::loadAtlas(std::filesystem::path path) {
    size_t atlasSize = 0;
    char* atlasData = graphics->assetFilesystem->loadAsset(path, atlasSize);

    if(!atlasData || atlasSize == 0) {
        std::cout << "SDFFont::loadAtlas Error loading atlas" << std::endl;
        return;
    }

    int components = 0;
    unsigned char* atlasImageData = stbi_load_from_memory((const unsigned char*)atlasData, atlasSize, &atlasWidth, &atlasHeight, &components, 0);

    if(components != 1) {
        std::cout << "SDFFont::loadAtlas Error, atlas contained " << components << " components, expected 1" << std::endl;
    }
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        atlasWidth,
        atlasHeight,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        atlasImageData
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(atlasImageData);
    graphics->assetFilesystem->freeFile(atlasData);
    std::cout << "FontAtlas::genTexture() -> Generated texture: " << textureId << std::endl;
}

void SDFFont::loadManifest(std::filesystem::path path) {
    size_t sdfManifestSize = 0;
    char* sdfManifestData = graphics->assetFilesystem->loadAsset(path, sdfManifestSize);
    if(!sdfManifestData || sdfManifestSize == 0) {
        std::cout << "SDFFont::loadManifest Error loading manifest" << std::endl;
        return;
    }

    nlohmann::json manifest = nlohmann::json::parse(std::string_view(sdfManifestData, sdfManifestSize));

    atlasWidth = manifest["width"];
    atlasHeight = manifest["height"];
    fontSize = manifest["size"];
    size = fontSize;

    if(manifest.contains("retina")) {
        if(manifest["retina"]) {
            retinaScale = manifest["retina_scale"].get<int>();
        }
    }

    if(manifest.contains("type")) {
        if(manifest["type"] == "bitmap") {
            shader = graphics->lazyLoadShader("shaders/atlas_text_bitmap");
        } else {
            shader = graphics->lazyLoadShader("shaders/atlas_text");
        }
    } else {
        shader = graphics->lazyLoadShader("shaders/atlas_text");
    }

    loadAtlas(path.parent_path()/manifest["atlas"]);

    float retinaScaleInv = 1.f / retinaScale;

    for(auto &i : manifest["characters"]) {
        float s = (float)i["sx"].get<int>() / (float)atlasWidth;
        float t = (float)i["sy"].get<int>() / (float)atlasHeight;
        float w = i["ex"].get<int>() - i["sx"].get<int>();
        float h = i["ey"].get<int>() - i["sy"].get<int>();
        float bearingX = i["bx"].get<int>();
        float bearingY = i["by"].get<int>();
        float advance = i["a"].get<int>();
        float uvW = w / (float)atlasWidth;
        float uvH = h / (float)atlasHeight;

        atlasEntries[i["c"].get<int>()] = {
            glm::vec4(s, t, uvW, uvH),
            glm::vec3(bearingX, bearingY, advance),
            glm::mat4(
                glm::scale(
                    glm::translate(
                        glm::identity<glm::mat4>(),
                        glm::vec3(bearingX * retinaScaleInv, -bearingY * retinaScaleInv, 0)
                    ),
                    glm::vec3(w * retinaScaleInv, h * retinaScaleInv, 1.)
                )
            )
        };
    }

    graphics->assetFilesystem->freeFile(sdfManifestData);
}

void SDFFont::renderTextSimple( 
    glm::vec3 position, 
    glm::vec3 col, 
    std::string_view text, 
    float &computedWidth,
    float weight, 
    float italics
) {  
    glUseProgram(shader->id);
    glUniform4fv(glGetUniformLocation(shader->id, "col"), 1, glm::value_ptr(col));

    glBindVertexArray(mesh->vao);
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    int cursor = 0;
    glm::vec3 originPos = position;
    for(auto &i : text) {
        auto ch = atlasEntries[i];
        glm::mat4 view = glm::translate(glm::identity<glm::mat4>(), position);
        glUniformMatrix4fv(glGetUniformLocation(shader->id, "mvp"), 1, false, glm::value_ptr(
            projectionMatrix * 
            view * 
            glm::shear(ch.model, glm::vec3(0.f, 0.f, 0), glm::vec2(-italics * .25, 0), glm::vec2(0.0f, 0), glm::vec2(0))
        ));
        glUniform4fv(glGetUniformLocation(shader->id, "atlasMetrics"), 1, glm::value_ptr(ch.atlasMetrics));
        glUniform1fv(glGetUniformLocation(shader->id, "weight"), 1, &weight);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh->indexCount);

        position.x += ch.fontMetrics.z / 64.;

        cursor++;
    }
    computedWidth = position.x - originPos.x;
}

SDFFont::SDFFont(
    Graphics* graphics, 
    std::filesystem::path path
) :graphics(graphics) {
    retinaScale = 1;
    textureId = 0;
    shader = nullptr;
    projectionMatrix = glm::mat4(glm::identity<glm::mat4>());
    mesh = graphics->findMesh("tlquad");
    if(!mesh) {
        // X, Y, Z, S, T
        std::vector<float> q = {
            0, 0, 0, 0, 0,
            1, 0, 0, 1, 0,
            0, 1, 0, 0, 1,
            1, 1, 0, 1, 1,
        };
        graphics->meshes.push_back(new Mesh("tlquad", q));
        mesh = graphics->findMesh("tlquad");
    }
    loadManifest(path);
}

SDFFont::~SDFFont() {
}

void SDFFont::setProjectionMatrix(glm::mat4 nProjectionMatrix) {
    projectionMatrix = nProjectionMatrix;
}