#include "Token.h"
#include "Constants.h"
#include "Functions.h"
#include "Parser.h"

Token::Token() : value(""), type(Type::TOKEN_NULL), depth(0), pairId(0) {
}

Token::Token(int type, std::string value) :type(type), value(value), depth(0), pairId(0) {
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

const bool Token::isParenthesis() {
    return isType(Token::TOKEN_OPEN_PARENTHESIS) || isType(Token::TOKEN_CLOSE_PARENTHESIS);
}

const bool Token::isType(int v) {
    return v == type;
}

bool Token::isConstantIdentifier() const {
    return Constants::exists(value);
}

bool Token::isFunctionIdentifier() const {
    return Functions::exists(value);
}

bool Token::isResolved() const {
    return isConstantIdentifier() || isFunctionIdentifier();
}

bool Token::isValidOperator() {
    if(value.length() != 1)
        return false;

    for(auto &i : Parser::operators) {
        if(i.first == value[0])
            return true;
    }

    return false;
}

glm::vec4 Token::getColor() {
    glm::vec3 num = glm::vec3(0., 255., 188) / glm::vec3(256.);
    glm::vec3 identifer = glm::vec3(251, 243, 0) / glm::vec3(256.);
    glm::vec3 unresolved = glm::vec3(241, 170, 18) / glm::vec3(256.);
    glm::vec3 constant = glm::vec3(174, 241, 18) / glm::vec3(256.);

    glm::vec3 oper = glm::vec3(184, 184, 184) / glm::vec3(256.);
    glm::vec3 parenths = glm::vec3(160, 160, 160) / glm::vec3(256.);

    const std::map<int, glm::vec3> tokenColours = {
        {Token::TOKEN_NUMBER, num},
        {Token::TOKEN_OPERATOR, oper},
        {Token::TOKEN_EXPRESSION, oper},
        {Token::TOKEN_WHITESPACE, glm::vec3(1., 1., 1.)},
        {Token::TOKEN_OPEN_PARENTHESIS, parenths},
        {Token::TOKEN_CLOSE_PARENTHESIS, parenths},
        {Token::TOKEN_COMMA, parenths},
        {Token::TOKEN_IDENTIFIER, identifer},
        {Token::TOKEN_FUNCTION, identifer},
        {Token::TOKEN_NULL, glm::vec3(1., 1., 1.)},
        {Token::TOKEN_UNKNOWN, glm::vec3(.5)},
    };

    glm::vec3 color = tokenColours.at(type);

    if(isType(Token::TOKEN_IDENTIFIER)) {
        if(!isResolved()) {
            color = unresolved;
        } else if (isConstantIdentifier()) {
            color = constant;
        }
    }

    return glm::vec4(color, 1.);
}

void Token::setDepth(int nDepth) {
    depth = nDepth;
}
int Token::getDepth() const {
    return depth;
}

void Token::setPairId(int nPairId) {
    pairId = nPairId;
}

int Token::getPairId() const {
    return pairId;
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
    {TOKEN_EXPRESSION, "TOKEN_EXPRESSION"},
    {TOKEN_WHITESPACE, "TOKEN_WHITESPACE"},
    {TOKEN_OPEN_PARENTHESIS, "TOKEN_OPEN_PARENTHESIS"},
    {TOKEN_CLOSE_PARENTHESIS, "TOKEN_CLOSE_PARENTHESIS"},
    {TOKEN_COMMA, "TOKEN_COMMA"},
    {TOKEN_IDENTIFIER, "TOKEN_IDENTIFIER"},
    {TOKEN_FUNCTION, "TOKEN_FUNCTION"},
    {TOKEN_NULL, "TOKEN_NULL"},
    {TOKEN_UNKNOWN, "TOKEN_UNKNOWN"},
};