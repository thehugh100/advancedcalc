#include "Helper.h"
#include <sstream>
#include <iomanip>
#include <limits>

std::string Helper::toStringWithMaximumPrecision(double value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(std::numeric_limits<double>::digits10) << value;
    return oss.str();
}

glm::mat4 Helper::quadMat(float x, float y, float w, float h) {
    glm::mat4 mat = glm::mat4(1.0f);
    mat = glm::translate(mat, glm::vec3(x, y, 0.0f));
    mat = glm::scale(mat, glm::vec3(w, h, 1.0f));
    return mat;
}