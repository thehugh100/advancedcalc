#pragma once

#include <memory>

class TokenList;
class Calculator;

class Lexer {
    public:
    Lexer(Calculator* calculator);
    bool lexInput(TokenList& tokenList);
    bool expandConstants(TokenList& tokenList);
    void expandVariables(TokenList& tokenList);

    Calculator* calculator;
    private:
};