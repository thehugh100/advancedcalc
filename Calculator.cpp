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
#include "CalcError.h"
#include "Constants.h"
#include "FunctionType.h"
#include "Instruction.h"
#include "InstructionVM.h"

Calculator::Calculator(bool debug)
    :debug(debug), lexer(std::make_shared<Lexer>(this)), parser(std::make_shared<Parser>(this)), vm(std::make_shared<InstructionVM>()) {
    parsed = new TokenList();
    validResult = true;
    clearErrors();
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

        if(tokenType == Token::TOKEN_COMMA) {
            reportError(new CalcError(token, "Unexpected comma"));
        } else if(tokenType == Token::TOKEN_IDENTIFIER) {
            Token refTkn = Token(tokenType, tokenValue);
            if(refTkn.isResolved()) {
                reportError(new CalcError(refTkn, "Missing function body"));
            } else {
                reportError(new CalcError(refTkn, "Unknown Identifier"));
            }
        } else if (tokenType == Token::TOKEN_NUMBER || tokenType == Token::TOKEN_FUNCTION) {
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
                if(!operatorStack.empty())
                    reportError(new CalcError(operatorStack.top(), "Mismatched Parentheses"));
                else
                    reportError(new CalcError(Token(Token::TOKEN_CLOSE_PARENTHESIS, ")"), "Mismatched Parentheses"));

                throw std::runtime_error("Mismatched parentheses");
            }

            operatorStack.pop();
        }
    }

    while (!operatorStack.empty()) {
        if (operatorStack.top().isType(Token::TOKEN_OPEN_PARENTHESIS) ||
            operatorStack.top().isType(Token::TOKEN_CLOSE_PARENTHESIS)) {
            reportError(new CalcError(operatorStack.top(), "Mismatched Parentheses"));
            throw std::runtime_error("Mismatched parentheses");
        }

        outputQueue.list.push_back(operatorStack.top());
        operatorStack.pop();
    }

    return outputQueue;
}

double Calculator::computeFunctionResult(const Token func) {
    TokenList tokens;
    parser->parseInput(func.getValue(), tokens);

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
            ParameterList_t params;
            for(auto &i : parameters) {
                if(i.list.size() == 0) {
                    reportError(new CalcError(identifier, "Empty parameter"));
                    throw std::runtime_error("Empty parameter");
                }
                params.push_back(processTokens(i));
            }
            return func.first(params);
        } else {
            reportError(new CalcError(identifier, "Too " + (parameters.size() >= func.second ? std::string("Many") : std::string("Few")) + " parameters."));
            throw std::runtime_error("Too " + (parameters.size() >= func.second ? std::string("Many") : std::string("Few")) + " parameters.");
        }
    } else {
        reportError(new CalcError(identifier, "Unknown function"));
        throw std::runtime_error("Unknown function " + identifier.getValue());
    }

    return 0.0;
}

void Calculator::compileFunctionCall(const Token func, std::vector<Instruction>& instructions, std::string &funcName) {
    TokenList tokens;
    parser->parseInput(func.getValue(), tokens);

    Token identifier = tokens.list[0];

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

    if(Functions::exists(identifier.getValue())) {
        funcName = identifier.getValue();
        auto func = Functions::get(identifier.getValue());
        if(parameters.size() == func.second) {
            for(auto &i : parameters) {
                lexer->lexInput(i);
                TokenList shunted = performShuntingYard(i);
                std::vector<Instruction> localByteCode;
                compileTokens(shunted, localByteCode);
                for(auto &i : localByteCode) {
                    instructions.push_back(i);
                }
            }
            return;
        }
    }
}

void Calculator::compileTokens(const TokenList& tokens, std::vector<Instruction>& instructions) {
    for (const auto& token : tokens.list) {
        if(token.isType(Token::TOKEN_NUMBER)) {
            instructions.push_back(
                Instruction(Instruction::OP_PUSH, Operand(Operand::TYPE_NUMBER, std::stod(token.getValue())))
            );
        } else if(token.isType(Token::TOKEN_OPERATOR)) {
            instructions.push_back(
                Instruction(Instruction::OP_OPERATOR, Operand(Operand::TYPE_OPERATOR, (char)token.getValue()[0]))
            );
        } else if(token.isType(Token::TOKEN_FUNCTION)) {
            std::vector<Instruction> funcByteCode;
            std::string funcName;
            compileFunctionCall(token, funcByteCode, funcName);
            for(auto &i : funcByteCode) {
                instructions.push_back(i);
            }
            instructions.push_back(
                Instruction(Instruction::OP_CALL, Operand(Operand::TYPE_FUNCTION, funcName))
            );
        }
    }
}

double Calculator::computeResult(const TokenList& outputQueue) {
    std::stack<double> operandStack;

    for (const auto& token : outputQueue.list) {
        const int tokenType = token.getType();
        std::string tokenValue = token.getValue();

        if (tokenType == Token::TOKEN_IDENTIFIER) {
            reportError(new CalcError(Token(tokenType, tokenValue), "Unknown Identifier"));
        } else if (tokenType == Token::TOKEN_NUMBER) {
            try {
                operandStack.push(std::stod(tokenValue));
            } catch(std::exception &e) {
                reportError(new CalcError(Token(tokenType, tokenValue), "Invalid Number"));
                return 0;
            }
        } else if (tokenType == Token::TOKEN_FUNCTION) {
            operandStack.push(computeFunctionResult(token));
        } else if (tokenType == Token::TOKEN_OPERATOR) {
            if(!Token(tokenType, tokenValue).isValidOperator()) {
                reportError(new CalcError(Token(tokenType, tokenValue), "Invalid Operator: " + tokenValue));
                throw std::runtime_error("Invalid expression");
            }

            if (operandStack.size() < 2) {
                reportError(new CalcError(Token(tokenType, tokenValue), "Invalid Expression: " + tokenValue + " requires 2 operands."));
                throw std::runtime_error("Invalid expression");
            }

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
                if (operand2 == 0) {
                    reportError(new CalcError(Token(tokenType, tokenValue), "Division by zero"));
                    throw std::runtime_error("Division by zero");
                }

                operandStack.push(operand1 / operand2);
            } else {
                reportError(new CalcError(Token(tokenType, tokenValue), "Invalid Operator"));
                throw std::runtime_error("Invalid operator");
            }
        }
    }

    if (operandStack.size() != 1) {
        reportError(new CalcError(Token(Token::TOKEN_EXPRESSION, parsed->toString()), "Incomplete expression"));
        throw std::runtime_error("Invalid expression");
    }

    return operandStack.top();
}

double Calculator::processTokens(TokenList& list) {
    lexer->lexInput(list);

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
        //error = e.what();
    }

    return result;
}

double Calculator::calculateInput(std::string_view input) {
    clearErrors();
    validResult = true;

    TokenList parsedInput;
    parser->parseInput(input, parsedInput);

    parsed->list.clear();
    for(auto&i : parsedInput.list) {
        parsed->list.push_back(i);
    }

    hintTokens(*parsed);

    if(debug) {
        std::cout << "---Input---" << std::endl;
        parsedInput.print();
    }

    return processTokens(parsedInput);
}

void Calculator::compileInput(std::string_view input) {
    calculateInput(input); //TODO: lame way to error check
    compiledInstructions.clear();
    if(validResult) {
        TokenList list;
        parser->parseInput(input, list);
        lexer->lexInput(list);
        TokenList shuntedList;
        shuntedList = performShuntingYard(list);

        compileTokens(shuntedList, compiledInstructions);
    }
}

void Calculator::setDebug(bool nDebug) {
    debug = nDebug;
}

void Calculator::hintTokens(TokenList& list) {
    int parenthesisDepth = 0;
    int pairId = 0;
    int deepestParenthesis = 0;

    for(auto &i : list.list) {
        int depthToSet = parenthesisDepth;
        if(i.isType(Token::TOKEN_OPEN_PARENTHESIS)) {
            parenthesisDepth++;
            depthToSet = parenthesisDepth;
        } else if(i.isType(Token::TOKEN_CLOSE_PARENTHESIS)) {
            parenthesisDepth--;
        }
        i.setDepth(depthToSet);
        if(depthToSet > deepestParenthesis) {
            deepestParenthesis = depthToSet;
        }
    }
    //assign a globally unique id to each parenthesis pair, this is for hilighting of each unique pair
    // ( ( () ), () )
    // 0 1 22 1  11 0
    // 0 1 22 1  33 0
    
    // This is horrible and is definitely doable in linear time...
    int uniqueId = 0;
    for(int i = 0; i < deepestParenthesis+1; i++) {
        for(auto &t : list.list) {
            if(t.getDepth() == i) {
                int idToSet = uniqueId;
                if(t.isType(Token::TOKEN_CLOSE_PARENTHESIS))
                    uniqueId++;
                t.setPairId(idToSet);
            }
        }
    }
}

bool Calculator::resultIsValid() {
    return validResult;
}

double Calculator::executeInstructions() {
    vm->execute(compiledInstructions);
    if(vm->getStack()->empty()) {
        reportError(new CalcError(Token(Token::TOKEN_EXPRESSION, parsed->toString()), "No result on stack"));
        return 0.0;
    }
    return vm->getStack()->top();
}

std::shared_ptr<std::vector<CalcError*>> Calculator::getErrors() {
    return std::make_shared<std::vector<CalcError*>>(errors);
}

void Calculator::reportError(CalcError* error) {
    errors.push_back(error);
    validResult = false;
}

void Calculator::clearErrors() {
    for(auto &i: errors) {
        delete i;
    }
    errors.clear();
}

std::vector<std::string> Calculator::getSuggestions(std::string_view input) {
    std::vector<std::string> suggestions;
    std::string upperName = std::string(input);
    std::transform(upperName.begin(), upperName.end(), upperName.begin(), [](unsigned char c){ return std::toupper(c); });

    //find functions that begin with input
    for(auto &i : Functions::getFunctions()) {
        if(i.first.find(input) == 0) {
            suggestions.push_back(i.first);
        }
    }
    //find constants that begin with input
    for(auto &i : Constants::getConstants()) {
        if(i.first.find(upperName) == 0) {
            suggestions.push_back(i.first);
        }
    }

    //sort suggestions by length
    std::sort(suggestions.begin(), suggestions.end(), [](const std::string& a, const std::string& b) {
        return a.size() < b.size();
    });

    return suggestions;
}