#pragma once

#include <map>
#include <string>

class Constants {
    public:
    static bool exists(std::string name);
    static double get(std::string name);

    private:
    static const std::map<std::string, double> constants;
};