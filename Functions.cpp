#include "Functions.h"
#include <math.h>
#include <cmath>

bool Functions::exists(std::string name) {
    return functions.find(name) != functions.end();
}

FunctionCallDefinition_t Functions::get(std::string name) {
    return functions.at(name);
}

FunctionList_t Functions::getFunctions() {
    return functions;
}

FunctionList_t Functions::functions = {
    {"max",
        {
            [](ParameterList_t params) {
                return std::max(params[0], params[1]);
            }, 
            2
        }
    },
    {"min",
        {
            [](ParameterList_t params) {
                return std::min(params[0], params[1]);
            }, 
            2
        }
    },
    {"saturate",
        {
            [](ParameterList_t params) {
                return std::max(0., std::min(1., params[0]));
            }, 
            1
        }
    },
    {"clamp",
        {
            [](ParameterList_t params) {
                return std::max(params[1], std::min(params[2], params[0]));
            }, 
            3
        }
    },
    {"sin",
        {
            [](ParameterList_t params) {
                return sin(params[0]);
            }, 
            1
        }
    },
    {"cos",
        {
            [](ParameterList_t params) {
                return cos(params[0]);
            }, 
            1
        }
    },
    {"tan",
        {
            [](ParameterList_t params) {
                return tan(params[0]);
            }, 
            1
        }
    },
    {"asin",
        {
            [](ParameterList_t params) {
                return asin(params[0]);
            }, 
            1
        }
    },
    {"acos",
        {
            [](ParameterList_t params) {
                return acos(params[0]);
            }, 
            1
        }
    },
    {"atan",
        {
            [](ParameterList_t params) {
                return atan(params[0]);
            }, 
            1
        }
    },
    {"atan2",
        {
            [](ParameterList_t params) {
                return atan2(params[0], params[1]);
            }, 
            2
        }
    },
    {"cosh",
        {
            [](ParameterList_t params) {
                return cosh(params[0]);
            }, 
            1
        }
    },
    {"tanh",
        {
            [](ParameterList_t params) {
                return tanh(params[0]);
            }, 
            1
        }
    },
    {"asinh",
        {
            [](ParameterList_t params) {
                return asinh(params[0]);
            }, 
            1
        }
    },
    {"acosh",
        {
            [](ParameterList_t params) {
                return acosh(params[0]);
            }, 
            1
        }
    },
    {"atanh",
        {
            [](ParameterList_t params) {
                return atanh(params[0]);
            }, 
            1
        }
    },
    {"sqrt",
        {
            [](ParameterList_t params) {
                return sqrt(params[0]);
            }, 
            1
        }
    },
    {"cbrt",
        {
            [](ParameterList_t params) {
                return cbrt(params[0]);
            }, 
            1
        }
    },
    {"rsqrt",
        {
            [](ParameterList_t params) {
                return pow(params[0], -0.5);
            }, 
            1
        }
    },
    {"abs",
        {
            [](ParameterList_t params) {
                return abs(params[0]);
            }, 
            1
        }
    },
    {"sign",
        {
            [](ParameterList_t params) {
                return std::copysign(1., params[0]);
            }, 
            1
        }
    },
    {"pow",
        {
            [](ParameterList_t params) {
                return pow(params[0], params[1]);
            }, 
            2
        }
    },
    {"exp",
        {
            [](ParameterList_t params) {
                return exp(params[0]);
            }, 
            1
        }
    },
    {"exp2",
        {
            [](ParameterList_t params) {
                return exp2(params[0]);
            }, 
            1
        }
    },
    {"exp10",
        {
            [](ParameterList_t params) {
                return pow(10, params[0]);
            }, 
            1
        }
    },
    {"log",
        {
            [](ParameterList_t params) {
                return log(params[0]);
            }, 
            1
        }
    },
    {"log2",
        {
            [](ParameterList_t params) {
                return log2(params[0]);
            }, 
            1
        }
    },
    {"log10",
        {
            [](ParameterList_t params) {
                return log10(params[0]);
            }, 
            1
        }
    },
    {"ceil",
        {
            [](ParameterList_t params) {
                return ceil(params[0]);
            }, 
            1
        }
    },
    {"floor",
        {
            [](ParameterList_t params) {
                return floor(params[0]);
            }, 
            1
        }
    },
    {"round",
        {
            [](ParameterList_t params) {
                return round(params[0]);
            }, 
            1
        }
    },
    {"fract",
        {
            [](ParameterList_t params) {
                return params[0] - floor(params[0]);
            }, 
            1
        }
    }
};