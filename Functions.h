#pragma once

#include <vector>
#include <functional>
#include <map>
#include <string>
#include <string_view>
#include <tuple>

class Functions {
    public:
    typedef std::vector<double> ParameterList_t;
    typedef std::function<double(ParameterList_t)> Function_t;
    typedef std::pair<Function_t, int> FunctionCallDefinition_t;
    typedef const std::map<std::string, FunctionCallDefinition_t> FunctionList_t;

    static FunctionList_t getFunctions();
    static bool exists(std::string name);
    static FunctionCallDefinition_t get(std::string name);

    private:
    static FunctionList_t functions;
};