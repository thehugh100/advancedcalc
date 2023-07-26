#pragma once
#include <memory>
#include <string>

#include "Token.h"

class CalcError {
    public:
    CalcError(Token token, std::string message);
    Token getToken();
    std::string getMessage();

    private:
    Token token;
    std::string message;
};