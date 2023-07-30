#include <vector>
#include <map>
#include <tuple>
#include <functional>

typedef std::vector<double> ParameterList_t;
typedef std::function<double(ParameterList_t)> Function_t;
typedef std::pair<Function_t, int> FunctionCallDefinition_t;
typedef const std::map<std::string, FunctionCallDefinition_t> FunctionList_t;