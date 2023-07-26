#include "Functions.h"
#include <math.h>
#include <cmath>

bool Functions::exists(std::string name) {
    return functions.find(name) != functions.end();
}

Functions::FunctionCallDefinition_t Functions::get(std::string name) {
    return functions.at(name);
}

Functions::FunctionList_t Functions::getFunctions() {
    return functions;
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
    {"saturate",
        {
            [](Functions::ParameterList_t params) {
                return std::max(0., std::min(1., params[0]));
            }, 
            1
        }
    },
    {"clamp",
        {
            [](Functions::ParameterList_t params) {
                return std::max(params[1], std::min(params[2], params[0]));
            }, 
            3
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
    {"tan",
        {
            [](Functions::ParameterList_t params) {
                return tan(params[0]);
            }, 
            1
        }
    },
    {"asin",
        {
            [](Functions::ParameterList_t params) {
                return asin(params[0]);
            }, 
            1
        }
    },
    {"acos",
        {
            [](Functions::ParameterList_t params) {
                return acos(params[0]);
            }, 
            1
        }
    },
    {"atan",
        {
            [](Functions::ParameterList_t params) {
                return atan(params[0]);
            }, 
            1
        }
    },
    {"atan2",
        {
            [](Functions::ParameterList_t params) {
                return atan2(params[0], params[1]);
            }, 
            2
        }
    },
    {"cosh",
        {
            [](Functions::ParameterList_t params) {
                return cosh(params[0]);
            }, 
            1
        }
    },
    {"tanh",
        {
            [](Functions::ParameterList_t params) {
                return tanh(params[0]);
            }, 
            1
        }
    },
    {"asinh",
        {
            [](Functions::ParameterList_t params) {
                return asinh(params[0]);
            }, 
            1
        }
    },
    {"acosh",
        {
            [](Functions::ParameterList_t params) {
                return acosh(params[0]);
            }, 
            1
        }
    },
    {"atanh",
        {
            [](Functions::ParameterList_t params) {
                return atanh(params[0]);
            }, 
            1
        }
    },
    {"sqrt",
        {
            [](Functions::ParameterList_t params) {
                return sqrt(params[0]);
            }, 
            1
        }
    },
    {"cbrt",
        {
            [](Functions::ParameterList_t params) {
                return cbrt(params[0]);
            }, 
            1
        }
    },
    {"rsqrt",
        {
            [](Functions::ParameterList_t params) {
                return pow(params[0], -0.5);
            }, 
            1
        }
    },
    {"abs",
        {
            [](Functions::ParameterList_t params) {
                return abs(params[0]);
            }, 
            1
        }
    },
    {"sign",
        {
            [](Functions::ParameterList_t params) {
                return std::copysign(1., params[0]);
            }, 
            1
        }
    },
    {"pow",
        {
            [](Functions::ParameterList_t params) {
                return pow(params[0], params[1]);
            }, 
            2
        }
    },
    {"exp",
        {
            [](Functions::ParameterList_t params) {
                return exp(params[0]);
            }, 
            1
        }
    },
    {"exp2",
        {
            [](Functions::ParameterList_t params) {
                return exp2(params[0]);
            }, 
            1
        }
    },
    {"exp10",
        {
            [](Functions::ParameterList_t params) {
                return pow(10, params[0]);
            }, 
            1
        }
    },
    {"log",
        {
            [](Functions::ParameterList_t params) {
                return log(params[0]);
            }, 
            1
        }
    },
    {"log2",
        {
            [](Functions::ParameterList_t params) {
                return log2(params[0]);
            }, 
            1
        }
    },
    {"log10",
        {
            [](Functions::ParameterList_t params) {
                return log10(params[0]);
            }, 
            1
        }
    },
    {"ceil",
        {
            [](Functions::ParameterList_t params) {
                return ceil(params[0]);
            }, 
            1
        }
    },
    {"floor",
        {
            [](Functions::ParameterList_t params) {
                return floor(params[0]);
            }, 
            1
        }
    },
    {"round",
        {
            [](Functions::ParameterList_t params) {
                return round(params[0]);
            }, 
            1
        }
    },
    {"fract",
        {
            [](Functions::ParameterList_t params) {
                return params[0] - floor(params[0]);
            }, 
            1
        }
    }
};