#pragma once

#include <string_view>
#include <string>

class Token;
class TokenList;
class Parser;
class Lexer;

class Calculator {
public:
    Calculator(bool debug);

    int getPrecedence(std::string_view in);
    TokenList performShuntingYard(const TokenList& tokens);
    double computeFunctionResult(const Token func);
    double computeResult(const TokenList& outputQueue);
    double processTokens(TokenList& list);
    double calculateInput(std::string_view input);
    void setDebug(bool nDebug);

    bool resultIsValid();
    std::string_view getError();

    TokenList* parsed;
private:
    bool debug;
    bool validResult;
    std::string error;
};