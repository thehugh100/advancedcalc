#include "Calculator.h"
#include <iostream>
#include <tuple>
#include <vector>
#include <stack>
#include <map>
#include <math.h>

#include "TokenList.h"
#include "Parser.h"
#include "Lexer.h"
#include "Token.h"
#include "Functions.h"

Calculator::Calculator(bool debug) : debug(debug) {
    parsed = new TokenList();
    validResult = true;
    error = "";
}

int Calculator::getPrecedence(std::string_view in) {
    char i = ' ';
    if(in.length() >= 1) {
        i = in[0];
        for(auto &o : Parser::operators) {
            if(i == o.first)
                return o.second;
        }
    }
    return 0;
}

TokenList Calculator::performShuntingYard(const TokenList& tokens) {
    std::stack<Token> operatorStack;
    TokenList outputQueue;

    for (const auto& token : tokens.list) {
        int tokenType = token.getType();
        std::string tokenValue = token.getValue();

        if (tokenType == Token::TOKEN_NUMBER || tokenType == Token::TOKEN_FUNCTION) {
            outputQueue.list.push_back(token);
        } else if (tokenType == Token::TOKEN_OPERATOR) {
            while (!operatorStack.empty() && operatorStack.top().isType(Token::TOKEN_OPERATOR) &&
                   getPrecedence(operatorStack.top().getValue()) >= getPrecedence(tokenValue)) {
                outputQueue.list.push_back(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(token);
        } else if (tokenType == Token::TOKEN_OPEN_PARENTHESIS) {
            operatorStack.push(token);
        } else if (tokenType == Token::TOKEN_CLOSE_PARENTHESIS) {
            while (!operatorStack.empty() && !operatorStack.top().isType(Token::TOKEN_OPEN_PARENTHESIS)) {
                outputQueue.list.push_back(operatorStack.top());
                operatorStack.pop();
            }

            if (operatorStack.empty() || !operatorStack.top().isType(Token::TOKEN_OPEN_PARENTHESIS)) {
                throw std::runtime_error("Mismatched parentheses");
            }

            operatorStack.pop();
        }
    }

    while (!operatorStack.empty()) {
        if (operatorStack.top().isType(Token::TOKEN_OPEN_PARENTHESIS) ||
            operatorStack.top().isType(Token::TOKEN_CLOSE_PARENTHESIS)) {
            throw std::runtime_error("Mismatched parentheses");
        }

        outputQueue.list.push_back(operatorStack.top());
        operatorStack.pop();
    }

    return outputQueue;
}

double Calculator::computeFunctionResult(const Token func) {
    TokenList tokens;
    Parser parser;
    parser.parseInput(func.getValue(), tokens);

    // std::cout << "---computeFunctionResult---" << std::endl;
    // printTokenList(tokens);

    if(tokens.list.size() < 3) {
        throw std::runtime_error("computeFunctionResult -> invalid function call, too few tokens");
    }

    Token identifier = tokens.list[0];

    if(!identifier.isType(Token::TOKEN_IDENTIFIER)) {
        throw std::runtime_error("computeFunctionResult -> First token is not an identifier");
    }

    std::vector<TokenList> parameters;
    parameters.push_back(TokenList());

    int parenthesisCount = 0;
    for(int i = 1; i < tokens.list.size(); ++i) {
        int tokenType = tokens.list[i].getType();
        if(tokenType == Token::TOKEN_OPEN_PARENTHESIS) {parenthesisCount++;}
        else if(tokenType == Token::TOKEN_CLOSE_PARENTHESIS) {parenthesisCount--;}

        if(tokenType == Token::TOKEN_OPEN_PARENTHESIS && parenthesisCount == 1) continue;
        if(tokenType == Token::TOKEN_CLOSE_PARENTHESIS && parenthesisCount == 0) continue;
        if(parenthesisCount == 1 && tokenType == Token::TOKEN_COMMA) {
            parameters.push_back(TokenList());
            continue;
        }

        parameters.back().list.push_back(tokens.list[i]);
    }

    // for(auto &i : parameters) {
    //     std::cout << "---computeFunctionResult--- parameter" << std::endl;
    //     printTokenList(i);
    // }

    if(Functions::exists(identifier.getValue())) {
        auto func = Functions::get(identifier.getValue());
        if(parameters.size() == func.second) {
            Functions::ParameterList_t params;
            for(auto &i : parameters) {
                params.push_back(processTokens(i));
            }
            return func.first(params);
        } else {
            throw std::runtime_error("Too " + (parameters.size() >= func.second ? std::string("Many") : std::string("Few")) + " parameters.");
        }
    } else {
        throw std::runtime_error("Unknown function " + identifier.getValue());
    }

    return 0.0;
}

double Calculator::computeResult(const TokenList& outputQueue) {
    std::stack<double> operandStack;

    for (const auto& token : outputQueue.list) {
        const int tokenType = token.getType();
        std::string tokenValue = token.getValue();

        if (tokenType == Token::TOKEN_NUMBER) {
            try {
                operandStack.push(std::stod(tokenValue));
            } catch(std::invalid_argument &e) {
                error = "Invalid number";
                validResult = false;
                return 0;
            }
        } else if (tokenType == Token::TOKEN_FUNCTION) {
            operandStack.push(computeFunctionResult(token));
        } else if (tokenType == Token::TOKEN_OPERATOR) {
            if (operandStack.size() < 2)
                throw std::runtime_error("Invalid expression");

            double operand2 = operandStack.top();
            operandStack.pop();
            double operand1 = operandStack.top();
            operandStack.pop();

            if (tokenValue == "+") {
                operandStack.push(operand1 + operand2);
            } else if (tokenValue == "-") {
                operandStack.push(operand1 - operand2);
            } else if (tokenValue == "*") {
                operandStack.push(operand1 * operand2);
            } else if (tokenValue == "^") {
                operandStack.push(pow(operand1, operand2));
            } else if (tokenValue == "%") {
                operandStack.push((int)operand1 % (int)operand2);
            } else if (tokenValue == "/") {
                if (operand2 == 0)
                    throw std::runtime_error("Division by zero");

                operandStack.push(operand1 / operand2);
            } else {
                throw std::runtime_error("Invalid operator");
            }
        }
    }

    if (operandStack.size() != 1)
        throw std::runtime_error("Invalid expression");

    return operandStack.top();
}

double Calculator::processTokens(TokenList& list) {
    Lexer lexer;
    lexer.lexInput(list);

    if(debug) {
        std::cout << "---Lexed Input---" << std::endl;
        list.print();
    }

    TokenList shuntedList;
    try {
        shuntedList = performShuntingYard(list);
    } catch (std::runtime_error &e) {
        if(debug)
            std::cout << "performShuntingYard() Error: " << e.what() << std::endl;

        validResult = false;
        error = e.what();
    }

    if(debug) {
        std::cout << "---Shunted---" << std::endl;
        shuntedList.print();
    }

    double result = 0.0;
    try {
        result = computeResult(shuntedList);
    } catch (std::runtime_error &e) {
        if(debug)
            std::cout << "computeResult() Error: " << e.what() << std::endl;

        validResult = false;
        error = e.what();
    }

    return result;
}

double Calculator::calculateInput(std::string_view input) {
    validResult = true;
    error = false;

    TokenList parsedInput;
    Parser parser;
    parser.parseInput(input, parsedInput);

    parsed->list.clear();
    for(auto&i : parsedInput.list) {
        parsed->list.push_back(i);
    }

    if(debug) {
        std::cout << "---Input---" << std::endl;
        parsedInput.print();
    }

    return processTokens(parsedInput);
}

void Calculator::setDebug(bool nDebug) {
    debug = nDebug;
}

bool Calculator::resultIsValid() {
    return validResult;
}

std::string_view Calculator::getError() {
    return error;
}