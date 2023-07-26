#pragma once

#include <string_view>
#include <string>
#include <vector>
#include <memory>

class Token;
class TokenList;
class Parser;
class Lexer;
class CalcError;

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
    
    void hintTokens(TokenList& list);


    void clearErrors();
    void reportError(CalcError* error);
    std::shared_ptr<std::vector<CalcError*>> getErrors();
    std::vector<std::string> getSuggestions(std::string_view input);

    bool resultIsValid();
    TokenList* parsed;
    std::shared_ptr<Lexer> lexer;
private:
    bool debug;
    bool validResult;
    std::vector<CalcError*> errors;
};