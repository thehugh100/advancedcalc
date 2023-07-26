#include "Constants.h"
#include <math.h>

bool Constants::exists(std::string name) {
    std::transform(name.begin(), name.end(), name.begin(), ::toupper);
    return constants.find(name) != constants.end();
}

double Constants::get(std::string name) {
    return constants.at(name);
}

const std::map<std::string, double> Constants::getConstants() {
    return constants;
}

const std::map<std::string, double> Constants::constants = {
    {"PI", M_PI},
    {"TAU", M_PI * 2},
    {"E", M_E},
};