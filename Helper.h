#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Helper {
    public:
    static std::string toStringWithMaximumPrecision(double value);
    static glm::mat4 quadMat(float x, float y, float w, float h);
};