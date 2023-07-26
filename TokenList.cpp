#include "TokenList.h"
#include "Token.h"

#include <iostream>

void TokenList::print() {
    for(auto &i : list) {
        std::cout << i.getName() << " : '" << i.getValue() << "'" << std::endl;
    }
}

void TokenList::printShort() {
    for(auto &i : list) {
        std::cout << i.getValue();
    }
    std::cout << std::endl;
}

std::string TokenList::toString() {
    std::string str = "";
    for(auto &i : list) {
        str += i.getValue();
    }
    return str;
}