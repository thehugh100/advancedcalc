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
class Instruction;
class InstructionVM;

class Calculator {
public:
    Calculator(bool debug);

    int getPrecedence(std::string_view in);
    TokenList performShuntingYard(const TokenList& tokens);
    double computeFunctionResult(const Token func);
    double computeResult(const TokenList& outputQueue);

    void compileInput(std::string_view input);
    void compileTokens(const TokenList& tokens, std::vector<Instruction>& instructions);
    void compileFunctionCall(const Token func, std::vector<Instruction>& instructions, std::string &funcName);

    double processTokens(TokenList& list);
    double calculateInput(std::string_view input);
    void setDebug(bool nDebug);
    
    void hintTokens(TokenList& list);

    void clearErrors();
    void reportError(CalcError* error);

    std::shared_ptr<std::vector<CalcError*>> getErrors();
    std::vector<std::string> getSuggestions(std::string_view input);
    std::vector<Instruction> compiledInstructions;

    bool resultIsValid();
    TokenList* parsed;

    double executeInstructions();

    std::shared_ptr<Parser> parser;
    std::shared_ptr<Lexer> lexer;
    std::shared_ptr<InstructionVM> vm;
private:
    bool debug;
    bool validResult;
    std::vector<CalcError*> errors;
};