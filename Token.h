#pragma once

#include <string>
#include <map>
#include <vector>
#include <glm/glm.hpp>

class Token;

class Token {
public:
    Token();
    Token(int type, std::string value);
    
    std::string getValue() const;
    void setValue(std::string nValue);

    int getType() const;
    void setType(int nType);
    const bool isParenthesis();
    bool isType(int v) const;

    bool isConstantIdentifier() const;
    bool isFunctionIdentifier() const;
    bool isResolved() const;

    bool isValidOperator();
    glm::vec4 getColor();
    
    void setDepth(int nDepth);
    int getDepth() const;

    void setPairId(int nPairId);
    int getPairId() const;

    std::string_view getName() const;

    enum Type {
        TOKEN_NULL = 0,
        TOKEN_EXPRESSION,
        TOKEN_WHITESPACE,
        TOKEN_NUMBER,
        TOKEN_VARIABLE,
        TOKEN_OPERATOR,
        TOKEN_OPEN_PARENTHESIS,
        TOKEN_CLOSE_PARENTHESIS,
        TOKEN_COMMA,
        TOKEN_IDENTIFIER,
        TOKEN_SEMICOLON,
        TOKEN_FUNCTION,
        TOKEN_UNKNOWN,
    };
private:
    int type;
    int depth;
    int pairId;
    std::string value;
    static const std::map<int, std::string> tokenNames;
};