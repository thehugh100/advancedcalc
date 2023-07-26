#include "CalcError.h"

CalcError::CalcError(Token token, std::string message) :token(token), message(message) {
}

Token CalcError::getToken() {
    return token;
}

std::string CalcError::getMessage() {
    return message;
}