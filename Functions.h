#pragma once

#include <vector>
#include <functional>
#include <map>
#include <string>
#include <string_view>
#include <tuple>

#include "FunctionType.h"

class Functions {
    public:
    static FunctionList_t getFunctions();
    static bool exists(std::string name);
    static FunctionCallDefinition_t get(std::string name);
    static FunctionCallDefinition_t* getPtr(std::string name);

    private:
    static FunctionList_t functions;
};