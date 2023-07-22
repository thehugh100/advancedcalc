#pragma once

#include <vector>
#include <string_view>

typedef std::pair<char, int> Operator_t;

class TokenList;

class Parser {
public:
    static bool isCharNumeric(char i);
    static bool isCharHex(char i);
    static bool isCharOperator(char i);
    static bool isCharComma(char i);
    static bool isCharIdentifierStart(char i);
    static bool isCharIdentifier(char i);
    static bool isCharOpenParenthesis(char i);
    static bool isCharCloseParenthesis(char i);
    static bool isCharParenthesis(char i);

    static int tokenTypeFromChar(int i);

    // Operator and precedence
    static const std::vector<Operator_t> operators;

    bool parseInput(std::string_view input, TokenList& tokenList);
};