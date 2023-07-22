#include "Token.h"

Token::Token() : value(""), type(Type::TOKEN_NULL) {
}

Token::Token(int type, std::string value) :type(type), value(value) {
}

std::string Token::getValue() const {
    return value;
}

void Token::setValue(std::string nValue) {
    value = nValue;
}

int Token::getType() const {
    return type;
}

void Token::setType(int nType) {
    type = nType;
}

const bool Token::isType(int v) {
    return v == type;
}

std::string_view Token::getName() const
{
    if(Token::tokenNames.find(type) != Token::tokenNames.end()) {
        return Token::tokenNames.at(type);
    }

    return std::string_view("ERROR TYPE");
}

const std::map<int, std::string> Token::tokenNames = {
    {TOKEN_NUMBER, "TOKEN_NUMBER"},
    {TOKEN_OPERATOR, "TOKEN_OPERATOR"},
    {TOKEN_WHITESPACE, "TOKEN_WHITESPACE"},
    {TOKEN_OPEN_PARENTHESIS, "TOKEN_OPEN_PARENTHESIS"},
    {TOKEN_CLOSE_PARENTHESIS, "TOKEN_CLOSE_PARENTHESIS"},
    {TOKEN_COMMA, "TOKEN_COMMA"},
    {TOKEN_IDENTIFIER, "TOKEN_IDENTIFIER"},
    {TOKEN_FUNCTION, "TOKEN_FUNCTION"},
    {TOKEN_NULL, "TOKEN_NULL"},
    {TOKEN_UNKNOWN, "TOKEN_UNKNOWN"},
};