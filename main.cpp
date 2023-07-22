#include <inttypes.h>
#include <iostream>
#include <string_view>
#include <tuple>
#include <vector>
#include <stack>
#include <map>

#include "Calculator.h"

void runTests() {
    Calculator calculator(false);
    const std::vector<std::pair<std::string, double>> testCases = {
        {"1+1", 2},
        {"1.5 + 1.5", 3},
        {"1.5 + -1.5", 0},
        {"-1 + -2 + (-1 * 2)", -5.0},
        {"0x0A + 10", 20},
        {"0xFF + -0x0F", 240},
        {"33-9+40-(30+15)", 19},
        {"TAU + PI + (-PI + -TAU)", 0.},
        {"max(1, max(1, 2))", 2.},
        {"((1+1))", 2.}
    };

    int passes = 0;
    for(auto &i : testCases) {
        double result = calculator.calculateInput(i.first);
        if(result != i.second) {
            std::cout << "Test case failed: '" << i.first << "', expected: " << i.second << ", got: " << result << std::endl;
            calculator.setDebug(true);
            calculator.calculateInput(i.first);
            calculator.setDebug(false);
        } else {
            passes++;
        }
    }
    std::cout << "Tests passed " << passes << "/" << testCases.size() << std::endl;
}

int main() {
    runTests();
    Calculator calculator(true);

    while(1) {
        std::cout << ">> ";
        std::string input = "";
        std::getline(std::cin, input);
        try {
            std::cout << calculator.calculateInput(input) << std::endl;
        } catch (std::runtime_error &e) {
            std::cout << e.what() << std::endl;
        }
    }
}