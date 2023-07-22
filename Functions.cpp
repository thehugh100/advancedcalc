#include "Functions.h"
#include <math.h>

bool Functions::exists(std::string name) {
    return functions.find(name) != functions.end();
}

Functions::FunctionCallDefinition_t Functions::get(std::string name) {
    return functions.at(name);
}

Functions::FunctionList_t Functions::functions = {
    {"max",
        {
            [](Functions::ParameterList_t params) {
                return std::max(params[0], params[1]);
            }, 
            2
        }
    },
    {"min",
        {
            [](Functions::ParameterList_t params) {
                return std::min(params[0], params[1]);
            }, 
            2
        }
    },
    {"sin",
        {
            [](Functions::ParameterList_t params) {
                return sin(params[0]);
            }, 
            1
        }
    },
    {"cos",
        {
            [](Functions::ParameterList_t params) {
                return cos(params[0]);
            }, 
            1
        }
    },
};