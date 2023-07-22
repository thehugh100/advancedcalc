#pragma once

class TokenList;

class Lexer {
    public:
    Lexer();
    bool lexInput(TokenList& tokenList);
    bool expandConstants(TokenList& tokenList);
};