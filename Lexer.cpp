#include <string>

#include "Lexer.h"
#include "Parser.h"
#include "Token.h"
#include "TokenList.h"
#include "Constants.h"
#include "Helper.h"

Lexer::Lexer() {
}

bool Lexer::lexInput(TokenList& tokenList) {
    TokenList original = tokenList;
    tokenList.list.clear();

    Token lastToken = {Token::TOKEN_NULL, ""};
    bool join = 0;

    std::string buf = "";
    bool joiningFunction = 0;
    bool joiningIdentifier = 0;
    int parenthesisCount = 0;

    original.list.erase(std::remove_if(original.list.begin(), original.list.end(),
        [](const Token& token) {
            return token.getType() == Token::TOKEN_WHITESPACE;
        }),
        original.list.end()
    );

    for(auto &i : original.list) {
        if(joiningFunction) {
            if(i.isType(Token::TOKEN_OPEN_PARENTHESIS)) {
                parenthesisCount++;
            } else if (i.isType(Token::TOKEN_CLOSE_PARENTHESIS)) {
                parenthesisCount--;
                if(parenthesisCount == 0) {
                    joiningFunction = 0;
                    joiningIdentifier = 0;
                }
            }

            buf += i.getValue();
            if(!joiningFunction) {
                Token func = {Token::TOKEN_FUNCTION, buf};
                tokenList.list.push_back(func);
                lastToken = func;
                buf = "";
            }
            continue;
        }

        if(i.isType(Token::TOKEN_OPEN_PARENTHESIS) && lastToken.isType(Token::TOKEN_IDENTIFIER)) {
            joiningFunction = true;
            parenthesisCount++;
            buf += i.getValue();
            continue;
        }
        if(!i.isType(Token::TOKEN_OPEN_PARENTHESIS) && lastToken.isType(Token::TOKEN_IDENTIFIER)) {
            joiningIdentifier = false;
            Token func = {Token::TOKEN_IDENTIFIER, buf};
            tokenList.list.push_back(func);
            lastToken = func;
            buf = "";
        }

        if(i.isType(Token::TOKEN_OPERATOR)) { // Handle Unary operators
            if(
                lastToken.isType(Token::TOKEN_NULL) || 
                lastToken.isType(Token::TOKEN_OPEN_PARENTHESIS) || 
                lastToken.isType(Token::TOKEN_COMMA) || 
                lastToken.isType(Token::TOKEN_OPERATOR) 
            ) {
                join = true;
                lastToken = i;
                continue;
            }
        }

        if(join) {
            join = false;
            tokenList.list.push_back({i.getType(), lastToken.getValue() + i.getValue()});
        } else {
            if(!i.isType(Token::TOKEN_IDENTIFIER)) {   
                tokenList.list.push_back({i.getType(), i.getValue()});
            } else {
                buf = i.getValue();
                joiningIdentifier = true;
            }
        }
        lastToken = i;
    }

    if(joiningIdentifier) {
        tokenList.list.push_back({Token::TOKEN_IDENTIFIER, buf});
    }

    return expandConstants(tokenList);
}

bool Lexer::expandConstants(TokenList& tokenList) {
    for(auto &i : tokenList.list) {
        if(i.isType(Token::TOKEN_IDENTIFIER)) {
            if(i.getValue().length() >= 1) {
                std::string constantName = i.getValue();
                for(auto &a : constantName)
                    a = std::toupper(a);

                double multiplier = 1.;

                if(Parser::isCharOperator(constantName[0])) { //handle -PI etc
                    constantName = i.getValue().substr(1);
                    multiplier = -1.;
                }

                if(Constants::exists(constantName)) {
                    i.setType(Token::TOKEN_NUMBER);
                    i.setValue(Helper::toStringWithMaximumPrecision(Constants::get(constantName) * multiplier));
                }
            }
        }
    }
    return true;
}