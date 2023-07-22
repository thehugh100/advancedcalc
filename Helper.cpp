#include "Helper.h"
#include <sstream>
#include <iomanip>
#include <limits>

std::string Helper::toStringWithMaximumPrecision(double value) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(std::numeric_limits<double>::digits10) << value;
    return oss.str();
}