#pragma once

#include <vector>
class Token;

class TokenList {
    public:
    std::vector<Token> list;

    void print();
    void printShort();
    std::string toString();
};