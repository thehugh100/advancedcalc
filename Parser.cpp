#include "Parser.h"
#include "Token.h"
#include "TokenList.h"

bool Parser::isCharNumeric(char i) {
    return (i >= '0' && i <= '9') || i == '.';
}

bool Parser::isCharHex(char i) {
    return (i >= '0' && i <= '9') || (tolower(i) >= 'a' && tolower(i) <= 'f') || tolower(i) == 'x';
}

bool Parser::isCharOperator(char i) {
    for(auto &o : operators) {
        if(i == o.first)
            return true;
    }
    return false;
}

bool Parser::isCharComma(char i) {
    return i == ',';
}

bool Parser::isCharIdentifierStart(char i) {
    return isalpha(i);
}

bool Parser::isCharIdentifier(char i) {
    return isalnum(i);
}

bool Parser::isCharOpenParenthesis(char i) {
    return i == '(';
}

bool Parser::isCharCloseParenthesis(char i) {
    return i == ')';
}

bool Parser::isCharParenthesis(char i) {
    return Parser::isCharOpenParenthesis(i) || Parser::isCharCloseParenthesis(i);
}

int Parser::tokenTypeFromChar(int i) {
    if (i == ' ') {
        return Token::TOKEN_WHITESPACE;
    } else if (Parser::isCharNumeric(i)) {
        return Token::TOKEN_NUMBER;
    } else if (Parser::isCharOperator(i)) {
        return Token::TOKEN_OPERATOR;
    } else if (Parser::isCharOpenParenthesis(i)) {
        return Token::TOKEN_OPEN_PARENTHESIS;
    } else if (Parser::isCharCloseParenthesis(i)) {
        return Token::TOKEN_CLOSE_PARENTHESIS;
    } else if (Parser::isCharComma(i)) {
        return Token::TOKEN_COMMA;
    } else if (Parser::isCharIdentifierStart(i)) {
        return Token::TOKEN_IDENTIFIER;
    } else {
        return Token::TOKEN_UNKNOWN;
    }
}

const std::vector<Operator_t> Parser::operators = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
    {'%', 2},
    {'^', 3},
};

bool Parser::parseInput(std::string_view input, TokenList& tokenList) {
    int lastTokenType = Token::TOKEN_NULL;
    std::string buf = "";

    for(auto &i : input) {
        int tokenType = Parser::tokenTypeFromChar(i);

        //Allow hex literals
        if(lastTokenType == Token::TOKEN_NUMBER && Parser::isCharHex(i)) {
            tokenType = Token::TOKEN_NUMBER;
        }

        if(lastTokenType == Token::TOKEN_IDENTIFIER && Parser::isCharIdentifier(i)) {
            tokenType = Token::TOKEN_IDENTIFIER;
        }

        if(tokenType == Token::TOKEN_CLOSE_PARENTHESIS) {
            if(buf.size() == 1 && Parser::isCharCloseParenthesis(buf[0])) {
                tokenList.list.push_back({Token::TOKEN_CLOSE_PARENTHESIS, buf});
                buf = "";
            }
        }

        if(tokenType == Token::TOKEN_OPEN_PARENTHESIS) {
            if(buf.size() == 1 && Parser::isCharOpenParenthesis(buf[0])) {
                tokenList.list.push_back({Token::TOKEN_OPEN_PARENTHESIS, buf});
                buf = "";
            }
        }

        if(tokenType != lastTokenType) {
            if(lastTokenType != Token::TOKEN_WHITESPACE && lastTokenType != Token::TOKEN_NULL) {
                tokenList.list.push_back({lastTokenType, buf});
            }
            buf = "";

            lastTokenType = tokenType;
        }
        buf += i;
    }

    if(buf != "") {
        if(lastTokenType != Token::TOKEN_WHITESPACE && lastTokenType != Token::TOKEN_NULL) {
            tokenList.list.push_back({lastTokenType, buf});
        }
    }

    return true;
}